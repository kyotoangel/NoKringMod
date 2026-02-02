# DSP
y[n] : « carrier signal » (/ sidechain signal)

x[n] : main signal

carrier[n] = max(1 - depth*abs(y[n]), 0)

output[n] = x[n] * carrier[n]

# Plugdata implementation

<img width="422" height="512" alt="image" src="https://github.com/user-attachments/assets/e2d58a54-23d6-4589-bc80-18ef9bb4c930" />
