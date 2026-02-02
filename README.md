# DSP
y[n] : « carrier signal » (/ sidechain signal)
x[n] : main signal
carrier[n] = max(1 - depth*abs(y[n]), 0)
output[n] = x[n] * carrier[n]
