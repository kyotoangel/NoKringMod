# VST Overview
<img width="403" height="222" alt="Capture d’écran 2026-02-02 à 19 21 12" src="https://github.com/user-attachments/assets/dec713f3-97e2-4529-8c0f-deabc8f51b96" />

# DSP
y[n] : « carrier signal » (/ sidechain signal)

x[n] : main signal

carrier[n] = max(1 - depth*abs(y[n]), 0) (depth being controlled by the big knob, float value from 0 to 1)

output[n] = x[n] * carrier[n]

# Plugdata implementation

<img width="422" height="512" alt="image" src="https://github.com/user-attachments/assets/e2d58a54-23d6-4589-bc80-18ef9bb4c930" />
