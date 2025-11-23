import pandas as pd
import numpy as np

# Read CSV files
cw_data = pd.read_csv('cwUsed.csv', delimiter=',', on_bad_lines='skip')
udp_data = pd.read_csv('udpPacketTransmissionInfo.csv', delimiter=',', on_bad_lines='skip')


# 1. MAC-layer Retransmission Rate
initial_cw = 15  
cw_data['retransmissions'] = np.log2((cw_data['Contetion Size'] + 1) / (initial_cw + 1)).astype(int)

avg_retransmissions = cw_data['retransmissions'].mean()
fraction_retransmitted = (cw_data['retransmissions'] > 0).mean()

print(f"Average retransmissions per packet: {avg_retransmissions:.2f}")
print(f"Fraction of packets retransmitted: {fraction_retransmitted:.2%}")

# 2. End-to-End Delay
avg_delay = udp_data['Delay'].mean()

print(f"Average end-to-end delay: {avg_delay:.6f} seconds")