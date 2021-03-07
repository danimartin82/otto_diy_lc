import plotly.graph_objects as go
from plotly.subplots import make_subplots
import pandas as pd
import sys

# Input data
filename=sys.argv[1]
df = pd.read_csv (filename)

labels=['time(s)','V(V1)','V(Label3)']

# Process data
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
# Plot Data

fig = make_subplots(rows=3, cols=1, subplot_titles=(labels[1], 'Duty','Frequency'))


fig.add_trace(go.Scatter(x=df[labels[0]], y=df[labels[1]]), row=1, col=1)
fig.add_trace(go.Scatter(x=df[labels[0]], y=df['Duty']), row=2, col=1)
fig.add_trace(go.Scatter(x=df[labels[0]], y=df['Frequency']), row=3, col=1)

fig.update_layout(
	title="Dub Siren: " + filename,
	xaxis_title="t [s]")
fig.update_xaxes(matches='x')
fig.update_layout(showlegend=False)

fig.show()