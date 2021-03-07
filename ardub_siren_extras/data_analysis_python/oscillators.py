import plotly.graph_objects as go
from plotly.subplots import make_subplots
import pandas as pd
import sys
import math


# Input data
filename='dub_siren_r6_low.csv' #sys.argv[1]
df = pd.read_csv (filename)

labels=['time(s)','V(V1)','V(Label3)']




freq_1 = 0
k = 0
tau = 0
period_1 = 0
semiperiod_1 = 0

amplitude = 5
offset = 0
aplied_offset = 0

########################################################################
# interpolate
########################################################################
def interpolate_f(freq):
	k = 0
	if (freq < freqs[0]):
		k = ks[0]

	elif freq > freqs[len(freqs)-1]:
		k = ks[len(ks)-1]

	else :	
		for i in range(len(freqs)):
		
			if freq == freqs[i]:
				k = ks[i]
				break

			if i < (len(freqs)-1):

				if	(freq > freqs[i]) & (freq < freqs[i+1]):
					y0=ks[i]
					y1=ks[i+1]
					x0=freqs[i]
					x1=freqs[i+1]					
					x=freq
					k = (y0*(x1-x)+y1*(x-x0))/(x1-x0)

	print("freq = " + str(freq) + " Hz, k= " + str(k))
	return k

########################################################################
# update_freq
########################################################################
def update_freq(freq):
		global period_1
		global semiperiod_1
		global k
		global tau
		period_1= 1 / freq
		semiperiod_1 = period_1 / 2
		k = interpolate_f(freq)
		tau = freq * k

def update_offset(offset):
	global aplied_offset
	aplied_offset= offset/100 * amplitude

########################################################################
# Generate signal 1 
########################################################################
freqs=[0.05,0.1,0.2,0.3,0.5,1,2,3,4,5]
ks=[200,100,10,4,2,0.2,0.1,0.08,0.04,0.03]


time_aux= df['time(s)']
step=time_aux[2]-time_aux[1]

my_signal_1 = [None] * len(time_aux)*20
time= [None] * len(my_signal_1)

# https://www.schoolphysics.co.uk/age16-19/Electricity%20and%20magnetism/Electrostatics/text/Capacitor_charge_and_discharge_mathematics/index.html

#Capacitor discharge (voltage decay): V = Voe-(t/RC)
#Capacitor charging (potential difference): V = Vo[1-e-(t/RC)] 

# Inputs
freq_1=0.03
update_freq(freq_1)


offset = 10 # [%]
update_offset(offset)


t = 0
value = 0
final_value = 0
check = False

for i in range(0,len(my_signal_1)):
	time[i]=i*step
	t= t + step
	if (t < semiperiod_1):
		value = amplitude* math.exp(-t/tau)
	if (t >= semiperiod_1):
		if check == False :
			final_value = amplitude* math.exp(-t/tau) + aplied_offset
			check = True
	if (t > semiperiod_1):
		value = final_value + amplitude*(1- math.exp(-(t-semiperiod_1)/tau))
	if (t >= period_1):	
		t = 0
		check = False
		
		freq_1=freq_1 + 0.05
		
		update_freq(freq_1)




	my_signal_1[i]=value




#df['my_signal_1']=my_signal_1


########################################################################
# Process data
########################################################################
freq = [None] * len(df)
duty = [None] * len(df)

t0=0
t1=0
t2=0
for i in range(0,len(df)):
	if i > 1:

		freq[i]=freq[i-1]
		duty[i]=duty[i-1]

		if (df.iloc[i,2] == 5) & (df.iloc[i-1,2] < 5):
			if t0==0:
				t0=df.iloc[i,0]
			else:
				t2=df.iloc[i,0]
				freq[i]=1/(t2-t0)
				duty[i]=(t1-t0)*100/(t2-t0)
				t0=t2
		if (df.iloc[i,2] < 5) & (df.iloc[i-1,2] == 5):
				t1=df.iloc[i,0]			

df['Frequency']=freq
df['Duty']=duty

########################################################################
# Plot Data
########################################################################
fig = make_subplots(rows=2, cols=1, subplot_titles=(labels[1], 'my_signal_1','Frequency'))


fig.add_trace(go.Scatter(x=df[labels[0]], y=df[labels[1]]), row=1, col=1)
fig.add_trace(go.Scatter(x=time, y=my_signal_1), row=2, col=1)



fig.update_layout(
	title="Dub Siren: " + filename,
	xaxis_title="t [s]")
fig.update_xaxes(matches='x')
fig.update_layout(showlegend=False)

fig.show()

