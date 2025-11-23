import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import glob

# === TASK 2 COMPREHENSIVE ANALYSIS ===

# Manual PDR and Throughput data provided by user
manual_data = {
    "Noise": {
        "Level1_110": {"PDR": 97.5, "Throughput": 5265, "Noise_dBm": -110},
        "Level2_105": {"PDR": 97.5, "Throughput": 5265, "Noise_dBm": -105},
        "Level3_100": {"PDR": 97.5, "Throughput": 5265, "Noise_dBm": -100},
        "Level4_95": {"PDR": 97.5, "Throughput": 5265, "Noise_dBm": -95},
        "Level5_90": {"PDR": 97.5, "Throughput": 5265, "Noise_dBm": -90},
        "Level6_86": {"PDR": 96.1, "Throughput": 5189.4, "Noise_dBm": -86}
    },
    "Transmission_Power": {
        "TxPower_20mW": {"PDR": 97.5, "Throughput": 5265, "Power_mW": 20},
        "TxPower_10mW": {"PDR": 97.5, "Throughput": 5265, "Power_mW": 10},
        "TxPower_5mW": {"PDR": 96.8, "Throughput": 5227.2, "Power_mW": 5},
        "TxPower_1mW": {"PDR": 45.3, "Throughput": 2446.2, "Power_mW": 1}
    },
    "Sensitivity": {
        "Sensitivity_85dBm": {"PDR": 97.5, "Throughput": 5265, "Sensitivity_dBm": -85},
        "Sensitivity_80dBm": {"PDR": 97.5, "Throughput": 5265, "Sensitivity_dBm": -80},
        "Sensitivity_75dBm": {"PDR": 83.4, "Throughput": 4527.9, "Sensitivity_dBm": -75},
        "Sensitivity_70dBm": {"PDR": 33.2, "Throughput": 1790.1, "Sensitivity_dBm": -70},
        "Sensitivity_65dBm": {"PDR": 9.8, "Throughput": 526.5, "Sensitivity_dBm": -65}
    }
}

def analyze_csv_files(folder_path, config_type, config_name):
    """Analyze CSV files in a given folder and return metrics"""
    results = {}
    
    # Find CSV files
    csv_files = glob.glob(os.path.join(folder_path, "*.csv"))
    
    for csv_file in csv_files:
        try:
            df = pd.read_csv(csv_file)
            filename = os.path.basename(csv_file)
            
            if "udpPacketTransmissionInfo" in filename:
                if "Delay" in df.columns:
                    results["End_to_End_Delay"] = {
                        "min": df["Delay"].min(),
                        "max": df["Delay"].max(),
                        "mean": df["Delay"].mean(),
                        "std": df["Delay"].std()
                    }
            
            elif "cwUsed" in filename:
                if "Contetion Size" in df.columns:  # Note: typo in original file
                    results["MAC_Retransmissions"] = {
                        "min": df["Contetion Size"].min(),
                        "max": df["Contetion Size"].max(),
                        "mean": df["Contetion Size"].mean(),
                        "std": df["Contetion Size"].std()
                    }
            
            elif "DataErrorRate" in filename:
                if "Error rate" in df.columns:
                    results["Data_Error_Rate"] = {
                        "min": df["Error rate"].min(),
                        "max": df["Error rate"].max(),
                        "mean": df["Error rate"].mean(),
                        "std": df["Error rate"].std()
                    }
                    
                    # Extract SNIR values from DataErrorRate.csv
                    if "SNIR" in df.columns:
                        results["SNIR"] = {
                            "min": df["SNIR"].min(),
                            "max": df["SNIR"].max(),
                            "mean": df["SNIR"].mean(),
                            "std": df["SNIR"].std()
                        }
            
            elif "HeaderErrorRate" in filename:
                if "Error rate" in df.columns:
                    results["Header_Error_Rate"] = {
                        "min": df["Error rate"].min(),
                        "max": df["Error rate"].max(),
                        "mean": df["Error rate"].mean(),
                        "std": df["Error rate"].std()
                    }
                    
                    # Extract SNIR values from HeaderErrorRate.csv (same as DataErrorRate.csv)
                    if "SNIR" in df.columns:
                        results["SNIR"] = {
                            "min": df["SNIR"].min(),
                            "max": df["SNIR"].max(),
                            "mean": df["SNIR"].mean(),
                            "std": df["SNIR"].std()
                        }
                    
                    # Calculate complete packet BER by combining header and data error rates
                    if "Header length" in df.columns and "Data length" in df.columns:
                        # Get data error rate from previous analysis if available
                        if "Data_Error_Rate" in results:
                            header_length = df["Header length"]
                            data_length = df["Data length"]
                            header_error_rate = df["Error rate"]
                            data_error_rate = results["Data_Error_Rate"]["mean"]  # Use mean for calculation
                            
                            # Calculate weighted average BER for complete packet
                            total_lengths = header_length + data_length
                            weighted_ber = (header_length * header_error_rate + 
                                          data_length * data_error_rate) / total_lengths
                            
                            results["Complete_Packet_BER"] = {
                                "min": weighted_ber.min(),
                                "max": weighted_ber.max(),
                                "mean": weighted_ber.mean(),
                                "std": weighted_ber.std()
                            }
                    
        except Exception as e:
            print(f"Error reading {csv_file}: {e}")
    
    return results

def create_comprehensive_analysis():
    """Create comprehensive analysis for Task 2"""
    
    # === ANALYSIS 1: Varying Noise Levels ===
    print("=== ANALYZING NOISE LEVEL CONFIGURATIONS ===")
    noise_analysis = {}
    
    for noise_level in ["Level1_110", "Level2_105", "Level3_100", "Level4_95", "Level5_90", "Level6_86"]:
        folder_path = f"task_2/Noise/{noise_level}"
        if os.path.exists(folder_path):
            print(f"\nAnalyzing {noise_level}...")
            csv_metrics = analyze_csv_files(folder_path, "Noise", noise_level)
            
            # Combine manual data with CSV analysis
            noise_analysis[noise_level] = {
                "Configuration": f"{noise_level}",
                "PDR_Manual": manual_data["Noise"][noise_level]["PDR"],
                "Throughput_Manual": manual_data["Noise"][noise_level]["Throughput"],
                "Noise_dBm": manual_data["Noise"][noise_level]["Noise_dBm"],
                **csv_metrics
            }
    
    # === ANALYSIS 2: Varying Transmission Power ===
    print("\n=== ANALYZING TRANSMISSION POWER CONFIGURATIONS ===")
    txpower_analysis = {}
    
    for txpower in ["TxPower_20mW", "TxPower_10mW", "TxPower_5mW", "TxPower_1mW"]:
        folder_path = f"task_2/Transmission Power/{txpower}"
        if os.path.exists(folder_path):
            print(f"\nAnalyzing {txpower}...")
            csv_metrics = analyze_csv_files(folder_path, "Transmission_Power", txpower)
            
            # Combine manual data with CSV analysis
            txpower_analysis[txpower] = {
                "Configuration": f"{txpower}",
                "PDR_Manual": manual_data["Transmission_Power"][txpower]["PDR"],
                "Throughput_Manual": manual_data["Transmission_Power"][txpower]["Throughput"],
                "Power_mW": manual_data["Transmission_Power"][txpower]["Power_mW"],
                **csv_metrics
            }
    
    # === ANALYSIS 3: Varying Receiver Sensitivity ===
    print("\n=== ANALYZING RECEIVER SENSITIVITY CONFIGURATIONS ===")
    sensitivity_analysis = {}
    
    for sensitivity in ["Sensitivity_85dBm", "Sensitivity_80dBm", "Sensitivity_75dBm", "Sensitivity_70dBm", "Sensitivity_65dBm"]:
        folder_path = f"task_2/Sensitivity/{sensitivity}"
        if os.path.exists(folder_path):
            print(f"\nAnalyzing {sensitivity}...")
            csv_metrics = analyze_csv_files(folder_path, "Sensitivity", sensitivity)
            
            # Combine manual data with CSV analysis
            sensitivity_analysis[sensitivity] = {
                "Configuration": f"{sensitivity}",
                "PDR_Manual": manual_data["Sensitivity"][sensitivity]["PDR"],
                "Throughput_Manual": manual_data["Sensitivity"][sensitivity]["Throughput"],
                "Sensitivity_dBm": manual_data["Sensitivity"][sensitivity]["Sensitivity_dBm"],
                **csv_metrics
            }
    
    return noise_analysis, txpower_analysis, sensitivity_analysis

def create_visualizations(noise_analysis, txpower_analysis, sensitivity_analysis):
    """Create comprehensive visualizations for Task 2"""
    
    # === CHART 1: Noise Level Analysis ===
    fig1, ((ax1, ax2), (ax3, ax4), (ax5, ax6)) = plt.subplots(3, 2, figsize=(16, 18))
    fig1.suptitle('Task 2: Performance Analysis - Varying Noise Levels', fontsize=16, fontweight='bold')
    
    noise_levels = list(noise_analysis.keys())
    noise_values = [noise_analysis[nl]["Noise_dBm"] for nl in noise_levels]
    
    # PDR vs Noise Level
    pdr_values = [noise_analysis[nl]["PDR_Manual"] for nl in noise_levels]
    ax1.plot(noise_values, pdr_values, marker='o', linestyle='-', color='blue', linewidth=2, markersize=8)
    ax1.set_title('Packet Delivery Ratio (PDR) vs Noise Level', fontweight='bold')
    ax1.set_xlabel('Noise Level (dBm)')
    ax1.set_ylabel('PDR (%)')
    ax1.grid(True, alpha=0.3)
    ax1.set_ylim(0, 100)
    
    # Throughput vs Noise Level
    throughput_values = [noise_analysis[nl]["Throughput_Manual"] for nl in noise_levels]
    ax2.plot(noise_values, throughput_values, marker='s', linestyle='-', color='green', linewidth=2, markersize=8)
    ax2.set_title('Throughput vs Noise Level', fontweight='bold')
    ax2.set_xlabel('Noise Level (dBm)')
    ax2.set_ylabel('Throughput (bytes/sec)')
    ax2.grid(True, alpha=0.3)
    
    # End-to-End Delay vs Noise Level (if available)
    delay_means = []
    for nl in noise_levels:
        if "End_to_End_Delay" in noise_analysis[nl]:
            delay_means.append(noise_analysis[nl]["End_to_End_Delay"]["mean"])
        else:
            delay_means.append(0)
    
    if any(d > 0 for d in delay_means):
        ax3.plot(noise_values, delay_means, marker='^', linestyle='-', color='red', linewidth=2, markersize=8)
        ax3.set_title('End-to-End Delay vs Noise Level', fontweight='bold')
        ax3.set_xlabel('Noise Level (dBm)')
        ax3.set_ylabel('Delay (seconds)')
        ax3.grid(True, alpha=0.3)
    else:
        ax3.text(0.5, 0.5, 'Delay data not available', ha='center', va='center', transform=ax3.transAxes)
        ax3.set_title('End-to-End Delay vs Noise Level', fontweight='bold')
    
    # MAC Retransmissions vs Noise Level (if available)
    retransmission_means = []
    for nl in noise_levels:
        if "MAC_Retransmissions" in noise_analysis[nl]:
            retransmission_means.append(noise_analysis[nl]["MAC_Retransmissions"]["mean"])
        else:
            retransmission_means.append(0)
    
    if any(r > 0 for r in retransmission_means):
        ax4.plot(noise_values, retransmission_means, marker='d', linestyle='-', color='orange', linewidth=2, markersize=8)
        ax4.set_title('MAC Retransmissions vs Noise Level', fontweight='bold')
        ax4.set_xlabel('Noise Level (dBm)')
        ax4.set_ylabel('Retransmissions')
        ax4.grid(True, alpha=0.3)
    else:
        ax4.text(0.5, 0.5, 'Retransmission data not available', ha='center', va='center', transform=ax4.transAxes)
        ax4.set_title('MAC Retransmissions vs Noise Level', fontweight='bold')
    
    # Data Error Rate vs Noise Level
    data_error_means = []
    for nl in noise_levels:
        if "Data_Error_Rate" in noise_analysis[nl]:
            data_error_means.append(noise_analysis[nl]["Data_Error_Rate"]["mean"])
        else:
            data_error_means.append(0)
    
    if any(e > 0 for e in data_error_means):
        ax5.plot(noise_values, data_error_means, marker='*', linestyle='-', color='purple', linewidth=2, markersize=8)
        ax5.set_title('Data Error Rate vs Noise Level', fontweight='bold')
        ax5.set_xlabel('Noise Level (dBm)')
        ax5.set_ylabel('Data Error Rate')
        ax5.grid(True, alpha=0.3)
    else:
        ax5.text(0.5, 0.5, 'Data Error Rate data not available', ha='center', va='center', transform=ax5.transAxes)
        ax5.set_title('Data Error Rate vs Noise Level', fontweight='bold')
    
    # SNIR vs Noise Level
    snir_means = []
    for nl in noise_levels:
        if "SNIR" in noise_analysis[nl]:
            snir_means.append(noise_analysis[nl]["SNIR"]["mean"])
        else:
            snir_means.append(0)
    
    if any(s > 0 for s in snir_means):
        ax6.plot(noise_values, snir_means, marker='h', linestyle='-', color='brown', linewidth=2, markersize=8)
        ax6.set_title('SNIR vs Noise Level', fontweight='bold')
        ax6.set_xlabel('Noise Level (dBm)')
        ax6.set_ylabel('SNIR')
        ax6.grid(True, alpha=0.3)
    else:
        ax6.text(0.5, 0.5, 'SNIR data not available', ha='center', va='center', transform=ax6.transAxes)
        ax6.set_title('SNIR vs Noise Level', fontweight='bold')
    
    plt.tight_layout()
    plt.savefig('task2_noise_analysis.png', dpi=300, bbox_inches='tight')
    
    # === CHART 2: Transmission Power Analysis ===
    fig2, ((ax1, ax2), (ax3, ax4), (ax5, ax6)) = plt.subplots(3, 2, figsize=(16, 18))
    fig2.suptitle('Task 2: Performance Analysis - Varying Transmission Power', fontsize=16, fontweight='bold')
    
    txpower_levels = list(txpower_analysis.keys())
    power_values = [txpower_analysis[tp]["Power_mW"] for tp in txpower_levels]
    
    # PDR vs Transmission Power
    pdr_values = [txpower_analysis[tp]["PDR_Manual"] for tp in txpower_levels]
    ax1.plot(power_values, pdr_values, marker='o', linestyle='-', color='blue', linewidth=2, markersize=8)
    ax1.set_title('Packet Delivery Ratio (PDR) vs Transmission Power', fontweight='bold')
    ax1.set_xlabel('Transmission Power (mW)')
    ax1.set_ylabel('PDR (%)')
    ax1.grid(True, alpha=0.3)
    ax1.set_ylim(0, 100)
    
    # Throughput vs Transmission Power
    throughput_values = [txpower_analysis[tp]["Throughput_Manual"] for tp in txpower_levels]
    ax2.plot(power_values, throughput_values, marker='s', linestyle='-', color='green', linewidth=2, markersize=8)
    ax2.set_title('Throughput vs Transmission Power', fontweight='bold')
    ax2.set_xlabel('Transmission Power (mW)')
    ax2.set_ylabel('Throughput (bytes/sec)')
    ax2.grid(True, alpha=0.3)
    
    # End-to-End Delay vs Transmission Power (if available)
    delay_means = []
    for tp in txpower_levels:
        if "End_to_End_Delay" in txpower_analysis[tp]:
            delay_means.append(txpower_analysis[tp]["End_to_End_Delay"]["mean"])
        else:
            delay_means.append(0)
    
    if any(d > 0 for d in delay_means):
        ax3.plot(power_values, delay_means, marker='^', linestyle='-', color='red', linewidth=2, markersize=8)
        ax3.set_title('End-to-End Delay vs Transmission Power', fontweight='bold')
        ax3.set_xlabel('Transmission Power (mW)')
        ax3.set_ylabel('Delay (seconds)')
        ax3.grid(True, alpha=0.3)
    else:
        ax3.text(0.5, 0.5, 'Delay data not available', ha='center', va='center', transform=ax3.transAxes)
        ax3.set_title('End-to-End Delay vs Transmission Power', fontweight='bold')
    
    # MAC Retransmissions vs Transmission Power (if available)
    retransmission_means = []
    for tp in txpower_levels:
        if "MAC_Retransmissions" in txpower_analysis[tp]:
            retransmission_means.append(txpower_analysis[tp]["MAC_Retransmissions"]["mean"])
        else:
            retransmission_means.append(0)
    
    if any(r > 0 for r in retransmission_means):
        ax4.plot(power_values, retransmission_means, marker='d', linestyle='-', color='orange', linewidth=2, markersize=8)
        ax4.set_title('MAC Retransmissions vs Transmission Power', fontweight='bold')
        ax4.set_xlabel('Transmission Power (mW)')
        ax4.set_ylabel('Retransmissions')
        ax4.grid(True, alpha=0.3)
    else:
        ax4.text(0.5, 0.5, 'Retransmission data not available', ha='center', va='center', transform=ax4.transAxes)
        ax4.set_title('MAC Retransmissions vs Transmission Power', fontweight='bold')
    
    # Data Error Rate vs Transmission Power
    data_error_means = []
    for tp in txpower_levels:
        if "Data_Error_Rate" in txpower_analysis[tp]:
            data_error_means.append(txpower_analysis[tp]["Data_Error_Rate"]["mean"])
        else:
            data_error_means.append(0)
    
    if any(e > 0 for e in data_error_means):
        ax5.plot(power_values, data_error_means, marker='*', linestyle='-', color='purple', linewidth=2, markersize=8)
        ax5.set_title('Data Error Rate vs Transmission Power', fontweight='bold')
        ax5.set_xlabel('Transmission Power (mW)')
        ax5.set_ylabel('Data Error Rate')
        ax5.grid(True, alpha=0.3)
    else:
        ax5.text(0.5, 0.5, 'Data Error Rate data not available', ha='center', va='center', transform=ax5.transAxes)
        ax5.set_title('Data Error Rate vs Transmission Power', fontweight='bold')
    
    # SNIR vs Transmission Power
    snir_means = []
    for tp in txpower_levels:
        if "SNIR" in txpower_analysis[tp]:
            snir_means.append(txpower_analysis[tp]["SNIR"]["mean"])
        else:
            snir_means.append(0)
    
    if any(s > 0 for s in snir_means):
        ax6.plot(power_values, snir_means, marker='h', linestyle='-', color='brown', linewidth=2, markersize=8)
        ax6.set_title('SNIR vs Transmission Power', fontweight='bold')
        ax6.set_xlabel('Transmission Power (mW)')
        ax6.set_ylabel('SNIR')
        ax6.grid(True, alpha=0.3)
    else:
        ax6.text(0.5, 0.5, 'SNIR data not available', ha='center', va='center', transform=ax6.transAxes)
        ax6.set_title('SNIR vs Transmission Power', fontweight='bold')
    
    plt.tight_layout()
    plt.savefig('task2_transmission_power_analysis.png', dpi=300, bbox_inches='tight')
    
    # === CHART 3: Receiver Sensitivity Analysis ===
    fig3, ((ax1, ax2), (ax3, ax4), (ax5, ax6)) = plt.subplots(3, 2, figsize=(16, 18))
    fig3.suptitle('Task 2: Performance Analysis - Varying Receiver Sensitivity', fontsize=16, fontweight='bold')
    
    sensitivity_levels = list(sensitivity_analysis.keys())
    sensitivity_values = [sensitivity_analysis[s]["Sensitivity_dBm"] for s in sensitivity_levels]
    
    # PDR vs Receiver Sensitivity
    pdr_values = [sensitivity_analysis[s]["PDR_Manual"] for s in sensitivity_levels]
    ax1.plot(sensitivity_values, pdr_values, marker='o', linestyle='-', color='blue', linewidth=2, markersize=8)
    ax1.set_title('Packet Delivery Ratio (PDR) vs Receiver Sensitivity', fontweight='bold')
    ax1.set_xlabel('Receiver Sensitivity (dBm)')
    ax1.set_ylabel('PDR (%)')
    ax1.grid(True, alpha=0.3)
    ax1.set_ylim(0, 100)
    
    # Throughput vs Receiver Sensitivity
    throughput_values = [sensitivity_analysis[s]["Throughput_Manual"] for s in sensitivity_levels]
    ax2.plot(sensitivity_values, throughput_values, marker='s', linestyle='-', color='green', linewidth=2, markersize=8)
    ax2.set_title('Throughput vs Receiver Sensitivity', fontweight='bold')
    ax2.set_xlabel('Receiver Sensitivity (dBm)')
    ax2.set_ylabel('Throughput (bytes/sec)')
    ax2.grid(True, alpha=0.3)
    
    # End-to-End Delay vs Receiver Sensitivity (if available)
    delay_means = []
    for s in sensitivity_levels:
        if "End_to_End_Delay" in sensitivity_analysis[s]:
            delay_means.append(sensitivity_analysis[s]["End_to_End_Delay"]["mean"])
        else:
            delay_means.append(0)
    
    if any(d > 0 for d in delay_means):
        ax3.plot(sensitivity_values, delay_means, marker='^', linestyle='-', color='red', linewidth=2, markersize=8)
        ax3.set_title('End-to-End Delay vs Receiver Sensitivity', fontweight='bold')
        ax3.set_xlabel('Receiver Sensitivity (dBm)')
        ax3.set_ylabel('Delay (seconds)')
        ax3.grid(True, alpha=0.3)
    else:
        ax3.text(0.5, 0.5, 'Delay data not available', ha='center', va='center', transform=ax3.transAxes)
        ax3.set_title('End-to-End Delay vs Receiver Sensitivity', fontweight='bold')
    
    # MAC Retransmissions vs Receiver Sensitivity (if available)
    retransmission_means = []
    for s in sensitivity_levels:
        if "MAC_Retransmissions" in sensitivity_analysis[s]:
            retransmission_means.append(sensitivity_analysis[s]["MAC_Retransmissions"]["mean"])
        else:
            retransmission_means.append(0)
    
    if any(r > 0 for r in retransmission_means):
        ax4.plot(sensitivity_values, retransmission_means, marker='d', linestyle='-', color='orange', linewidth=2, markersize=8)
        ax4.set_title('MAC Retransmissions vs Receiver Sensitivity', fontweight='bold')
        ax4.set_xlabel('Receiver Sensitivity (dBm)')
        ax4.set_ylabel('Retransmissions')
        ax4.grid(True, alpha=0.3)
    else:
        ax4.text(0.5, 0.5, 'Retransmission data not available', ha='center', va='center', transform=ax4.transAxes)
        ax4.set_title('MAC Retransmissions vs Receiver Sensitivity', fontweight='bold')
    
    # Data Error Rate vs Receiver Sensitivity
    data_error_means = []
    for s in sensitivity_levels:
        if "Data_Error_Rate" in sensitivity_analysis[s]:
            data_error_means.append(sensitivity_analysis[s]["Data_Error_Rate"]["mean"])
        else:
            data_error_means.append(0)
    
    if any(e > 0 for e in data_error_means):
        ax5.plot(sensitivity_values, data_error_means, marker='*', linestyle='-', color='purple', linewidth=2, markersize=8)
        ax5.set_title('Data Error Rate vs Receiver Sensitivity', fontweight='bold')
        ax5.set_xlabel('Receiver Sensitivity (dBm)')
        ax5.set_ylabel('Data Error Rate')
        ax5.grid(True, alpha=0.3)
    else:
        ax5.text(0.5, 0.5, 'Data Error Rate data not available', ha='center', va='center', transform=ax5.transAxes)
        ax5.set_title('Data Error Rate vs Receiver Sensitivity', fontweight='bold')
    
    # SNIR vs Receiver Sensitivity
    snir_means = []
    for s in sensitivity_levels:
        if "SNIR" in sensitivity_analysis[s]:
            snir_means.append(sensitivity_analysis[s]["SNIR"]["mean"])
        else:
            snir_means.append(0)
    
    if any(s > 0 for s in snir_means):
        ax6.plot(sensitivity_values, snir_means, marker='h', linestyle='-', color='brown', linewidth=2, markersize=8)
        ax6.set_title('SNIR vs Receiver Sensitivity', fontweight='bold')
        ax6.set_xlabel('Receiver Sensitivity (dBm)')
        ax6.set_ylabel('SNIR')
        ax6.grid(True, alpha=0.3)
    else:
        ax6.text(0.5, 0.5, 'SNIR data not available', ha='center', va='center', transform=ax6.transAxes)
        ax6.set_title('SNIR vs Receiver Sensitivity', fontweight='bold')
    
    plt.tight_layout()
    plt.savefig('task2_sensitivity_analysis.png', dpi=300, bbox_inches='tight')
    
    # === CHART 4: Comprehensive BER and SNIR Analysis ===
    fig4, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(16, 12))
    fig4.suptitle('Task 2: Comprehensive BER and SNIR Analysis Across All Parameters', fontsize=16, fontweight='bold')
    
    # Prepare data for comprehensive analysis
    all_configs = []
    all_data_errors = []
    all_header_errors = []
    all_snir = []
    all_labels = []
    
    # Add Noise Level data
    for noise_level in noise_levels:
        if "Data_Error_Rate" in noise_analysis[noise_level]:
            all_configs.append(f"Noise {noise_analysis[noise_level]['Noise_dBm']} dBm")
            all_data_errors.append(noise_analysis[noise_level]["Data_Error_Rate"]["mean"])
            all_header_errors.append(noise_analysis[noise_level]["Header_Error_Rate"]["mean"])
            all_snir.append(noise_analysis[noise_level]["SNIR"]["mean"])
            all_labels.append("Noise")
    
    # Add Transmission Power data
    for txpower in txpower_levels:
        if "Data_Error_Rate" in txpower_analysis[txpower]:
            all_configs.append(f"Power {txpower_analysis[txpower]['Power_mW']} mW")
            all_data_errors.append(txpower_analysis[txpower]["Data_Error_Rate"]["mean"])
            all_header_errors.append(txpower_analysis[txpower]["Header_Error_Rate"]["mean"])
            all_snir.append(txpower_analysis[txpower]["SNIR"]["mean"])
            all_labels.append("Power")
    
    # Add Receiver Sensitivity data
    for sensitivity in sensitivity_levels:
        if "Data_Error_Rate" in sensitivity_analysis[sensitivity]:
            all_configs.append(f"Sens {sensitivity_analysis[sensitivity]['Sensitivity_dBm']} dBm")
            all_data_errors.append(sensitivity_analysis[sensitivity]["Data_Error_Rate"]["mean"])
            all_header_errors.append(sensitivity_analysis[sensitivity]["Header_Error_Rate"]["mean"])
            all_snir.append(sensitivity_analysis[sensitivity]["SNIR"]["mean"])
            all_labels.append("Sensitivity")
    
    # Data Error Rate vs Configuration
    x_pos = range(len(all_configs))
    ax1.bar(x_pos, all_data_errors, color=['blue' if l == 'Noise' else 'green' if l == 'Power' else 'red' for l in all_labels])
    ax1.set_title('Data Error Rate Across All Configurations', fontweight='bold')
    ax1.set_xlabel('Configuration')
    ax1.set_ylabel('Data Error Rate')
    ax1.set_xticks(x_pos)
    ax1.set_xticklabels(all_configs, rotation=45, ha='right')
    ax1.grid(True, alpha=0.3)
    
    # Header Error Rate vs Configuration
    ax2.bar(x_pos, all_header_errors, color=['blue' if l == 'Noise' else 'green' if l == 'Power' else 'red' for l in all_labels])
    ax2.set_title('Header Error Rate Across All Configurations', fontweight='bold')
    ax2.set_xlabel('Configuration')
    ax2.set_ylabel('Header Error Rate')
    ax2.set_xticks(x_pos)
    ax2.set_xticklabels(all_configs, rotation=45, ha='right')
    ax2.grid(True, alpha=0.3)
    
    # SNIR vs Configuration
    ax3.bar(x_pos, all_snir, color=['blue' if l == 'Noise' else 'green' if l == 'Power' else 'red' for l in all_labels])
    ax3.set_title('SNIR Across All Configurations', fontweight='bold')
    ax3.set_xlabel('Configuration')
    ax3.set_ylabel('SNIR')
    ax3.set_xticks(x_pos)
    ax3.set_xticklabels(all_configs, rotation=45, ha='right')
    ax3.grid(True, alpha=0.3)
    
    # Error Rate Comparison (Data vs Header)
    ax4.plot(x_pos, all_data_errors, marker='o', linestyle='-', color='red', linewidth=2, markersize=8, label='Data Error Rate')
    ax4.plot(x_pos, all_header_errors, marker='s', linestyle='-', color='blue', linewidth=2, markersize=8, label='Header Error Rate')
    ax4.set_title('Data vs Header Error Rate Comparison', fontweight='bold')
    ax4.set_xlabel('Configuration')
    ax4.set_ylabel('Error Rate')
    ax4.set_xticks(x_pos)
    ax4.set_xticklabels(all_configs, rotation=45, ha='right')
    ax4.legend()
    ax4.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('task2_ber_snir_comprehensive_analysis.png', dpi=300, bbox_inches='tight')
    
    plt.show()

def create_summary_csv(noise_analysis, txpower_analysis, sensitivity_analysis):
    """Create comprehensive summary CSV with all metrics"""
    
    # Prepare data for CSV
    summary_data = []
    
    # Add Noise Level Analysis
    for noise_level, data in noise_analysis.items():
        # Calculate Cumulative Network Load (bps) - 50 hosts, 100B packets, 1s interval
        host_count = 50
        message_length_bits = 100 * 8  # 100 bytes = 800 bits
        send_interval = 1  # 1 second
        cumulative_load = host_count * (message_length_bits / send_interval)
        
        row = {
            "Configuration_Type": "Noise_Level",
            "Configuration_Name": data["Configuration"],
            "Noise_dBm": data["Noise_dBm"],
            "Host_Count": host_count,
            "PDR_Manual": data["PDR_Manual"],
            "Throughput_Manual": data["Throughput_Manual"],
            "Message_Length_Bytes": 100,
            "Send_Interval_Seconds": 1,
            "Cumulative_Network_Load_bps": cumulative_load
        }
        
        # Add CSV-derived metrics if available
        if "End_to_End_Delay" in data:
            row.update({
                "Delay_Min": data["End_to_End_Delay"]["min"],
                "Delay_Max": data["End_to_End_Delay"]["max"],
                "Delay_Mean": data["End_to_End_Delay"]["mean"],
                "Delay_Std": data["End_to_End_Delay"]["std"]
            })
        
        if "MAC_Retransmissions" in data:
            row.update({
                "Retransmissions_Min": data["MAC_Retransmissions"]["min"],
                "Retransmissions_Max": data["MAC_Retransmissions"]["max"],
                "Retransmissions_Mean": data["MAC_Retransmissions"]["mean"],
                "Retransmissions_Std": data["MAC_Retransmissions"]["std"]
            })
        
        if "Data_Error_Rate" in data:
            row.update({
                "Data_Error_Min": data["Data_Error_Rate"]["min"],
                "Data_Error_Max": data["Data_Error_Rate"]["max"],
                "Data_Error_Mean": data["Data_Error_Rate"]["mean"],
                "Data_Error_Std": data["Data_Error_Rate"]["std"]
            })
        
        if "Header_Error_Rate" in data:
            row.update({
                "Header_Error_Min": data["Header_Error_Rate"]["min"],
                "Header_Error_Max": data["Header_Error_Rate"]["max"],
                "Header_Error_Mean": data["Header_Error_Rate"]["mean"],
                "Header_Error_Std": data["Header_Error_Rate"]["std"]
            })
        
        if "Complete_Packet_BER" in data:
            row.update({
                "Complete_BER_Min": data["Complete_Packet_BER"]["min"],
                "Complete_BER_Max": data["Complete_Packet_BER"]["max"],
                "Complete_BER_Mean": data["Complete_Packet_BER"]["mean"],
                "Complete_BER_Std": data["Complete_Packet_BER"]["std"]
            })
        
        if "SNIR" in data:
            row.update({
                "SNIR_Min": data["SNIR"]["min"],
                "SNIR_Max": data["SNIR"]["max"],
                "SNIR_Mean": data["SNIR"]["mean"],
                "SNIR_Std": data["SNIR"]["std"]
            })
        
        summary_data.append(row)
    
    # Add Transmission Power Analysis
    for txpower, data in txpower_analysis.items():
        # Calculate Cumulative Network Load (bps) - 50 hosts, 100B packets, 1s interval
        host_count = 50
        message_length_bits = 100 * 8  # 100 bytes = 800 bits
        send_interval = 1  # 1 second
        cumulative_load = host_count * (message_length_bits / send_interval)
        
        row = {
            "Configuration_Type": "Transmission_Power",
            "Configuration_Name": data["Configuration"],
            "Power_mW": data["Power_mW"],
            "Host_Count": host_count,
            "PDR_Manual": data["PDR_Manual"],
            "Throughput_Manual": data["Throughput_Manual"],
            "Message_Length_Bytes": 100,
            "Send_Interval_Seconds": 1,
            "Cumulative_Network_Load_bps": cumulative_load
        }
        
        # Add CSV-derived metrics if available
        if "End_to_End_Delay" in data:
            row.update({
                "Delay_Min": data["End_to_End_Delay"]["min"],
                "Delay_Max": data["End_to_End_Delay"]["max"],
                "Delay_Mean": data["End_to_End_Delay"]["mean"],
                "Delay_Std": data["End_to_End_Delay"]["std"]
            })
        
        if "MAC_Retransmissions" in data:
            row.update({
                "Retransmissions_Min": data["MAC_Retransmissions"]["min"],
                "Retransmissions_Max": data["MAC_Retransmissions"]["max"],
                "Retransmissions_Mean": data["MAC_Retransmissions"]["mean"],
                "Retransmissions_Std": data["MAC_Retransmissions"]["std"]
            })
        
        if "Data_Error_Rate" in data:
            row.update({
                "Data_Error_Min": data["Data_Error_Rate"]["min"],
                "Data_Error_Max": data["Data_Error_Rate"]["max"],
                "Data_Error_Mean": data["Data_Error_Rate"]["mean"],
                "Data_Error_Std": data["Data_Error_Rate"]["std"]
            })
        
        if "Header_Error_Rate" in data:
            row.update({
                "Header_Error_Min": data["Header_Error_Rate"]["min"],
                "Header_Error_Max": data["Header_Error_Rate"]["max"],
                "Header_Error_Mean": data["Header_Error_Rate"]["mean"],
                "Header_Error_Std": data["Header_Error_Rate"]["std"]
            })
        
        if "Complete_Packet_BER" in data:
            row.update({
                "Complete_BER_Min": data["Complete_Packet_BER"]["min"],
                "Complete_BER_Max": data["Complete_Packet_BER"]["max"],
                "Complete_BER_Mean": data["Complete_Packet_BER"]["mean"],
                "Complete_BER_Std": data["Complete_Packet_BER"]["std"]
            })
        
        if "SNIR" in data:
            row.update({
                "SNIR_Min": data["SNIR"]["min"],
                "SNIR_Max": data["SNIR"]["max"],
                "SNIR_Mean": data["SNIR"]["mean"],
                "SNIR_Std": data["SNIR"]["std"]
            })
        
        summary_data.append(row)
    
    # Add Receiver Sensitivity Analysis
    for sensitivity, data in sensitivity_analysis.items():
        # Calculate Cumulative Network Load (bps) - 50 hosts, 100B packets, 1s interval
        host_count = 50
        message_length_bits = 100 * 8  # 100 bytes = 800 bits
        send_interval = 1  # 1 second
        cumulative_load = host_count * (message_length_bits / send_interval)
        
        row = {
            "Configuration_Type": "Receiver_Sensitivity",
            "Configuration_Name": data["Configuration"],
            "Sensitivity_dBm": data["Sensitivity_dBm"],
            "Host_Count": host_count,
            "PDR_Manual": data["PDR_Manual"],
            "Throughput_Manual": data["Throughput_Manual"],
            "Message_Length_Bytes": 100,
            "Send_Interval_Seconds": 1,
            "Cumulative_Network_Load_bps": cumulative_load
        }
        
        # Add CSV-derived metrics if available
        if "End_to_End_Delay" in data:
            row.update({
                "Delay_Min": data["End_to_End_Delay"]["min"],
                "Delay_Max": data["End_to_End_Delay"]["max"],
                "Delay_Mean": data["End_to_End_Delay"]["mean"],
                "Delay_Std": data["End_to_End_Delay"]["std"]
            })
        
        if "MAC_Retransmissions" in data:
            row.update({
                "Retransmissions_Min": data["MAC_Retransmissions"]["min"],
                "Retransmissions_Max": data["MAC_Retransmissions"]["max"],
                "Retransmissions_Mean": data["MAC_Retransmissions"]["mean"],
                "Retransmissions_Std": data["MAC_Retransmissions"]["std"]
            })
        
        if "Data_Error_Rate" in data:
            row.update({
                "Data_Error_Min": data["Data_Error_Rate"]["min"],
                "Data_Error_Max": data["Data_Error_Rate"]["max"],
                "Data_Error_Mean": data["Data_Error_Rate"]["mean"],
                "Data_Error_Std": data["Data_Error_Rate"]["std"]
            })
        
        if "Header_Error_Rate" in data:
            row.update({
                "Header_Error_Min": data["Header_Error_Rate"]["min"],
                "Header_Error_Max": data["Header_Error_Rate"]["max"],
                "Header_Error_Mean": data["Header_Error_Rate"]["mean"],
                "Header_Error_Std": data["Header_Error_Rate"]["std"]
            })
        
        if "Complete_Packet_BER" in data:
            row.update({
                "Complete_BER_Min": data["Complete_Packet_BER"]["min"],
                "Complete_BER_Max": data["Complete_Packet_BER"]["max"],
                "Complete_BER_Mean": data["Complete_Packet_BER"]["mean"],
                "Complete_BER_Std": data["Complete_Packet_BER"]["std"]
            })
        
        if "SNIR" in data:
            row.update({
                "SNIR_Min": data["SNIR"]["min"],
                "SNIR_Max": data["SNIR"]["max"],
                "SNIR_Mean": data["SNIR"]["mean"],
                "SNIR_Std": data["SNIR"]["std"]
            })
        
        summary_data.append(row)
    
    # Create DataFrame and save
    summary_df = pd.DataFrame(summary_data)
    summary_df.to_csv('task2_comprehensive_summary.csv', index=False)
    
    print(f"\n✅ Comprehensive summary saved to 'task2_comprehensive_summary.csv'")
    print(f"📊 Summary contains {len(summary_df)} configurations with all metrics")
    
    return summary_df

def main():
    """Main execution function"""
    print("🚀 Starting Task 2 Comprehensive Analysis...")
    
    # Perform analysis
    noise_analysis, txpower_analysis, sensitivity_analysis = create_comprehensive_analysis()
    
    # Create visualizations
    print("\n📈 Creating visualizations...")
    create_visualizations(noise_analysis, txpower_analysis, sensitivity_analysis)
    
    # Create summary CSV
    print("\n💾 Creating comprehensive summary CSV...")
    summary_df = create_summary_csv(noise_analysis, txpower_analysis, sensitivity_analysis)
    
    # Display summary
    print("\n📋 ANALYSIS SUMMARY:")
    print("=" * 50)
    
    print("\n🔊 NOISE LEVEL ANALYSIS:")
    for noise_level, data in noise_analysis.items():
        print(f"  {noise_level}: PDR={data['PDR_Manual']:.1f}%, Throughput={data['Throughput_Manual']:,.0f} bytes/sec, Noise={data['Noise_dBm']} dBm")
    
    print("\n⚡ TRANSMISSION POWER ANALYSIS:")
    for txpower, data in txpower_analysis.items():
        print(f"  {txpower}: PDR={data['PDR_Manual']:.1f}%, Throughput={data['Throughput_Manual']:,.0f} bytes/sec, Power={data['Power_mW']} mW")
    
    print("\n📡 RECEIVER SENSITIVITY ANALYSIS:")
    for sensitivity, data in sensitivity_analysis.items():
        print(f"  {sensitivity}: PDR={data['PDR_Manual']:.1f}%, Throughput={data['Throughput_Manual']:,.0f} bytes/sec, Sensitivity={data['Sensitivity_dBm']} dBm")
    
    print("\n✅ Analysis complete! Check the generated files:")
    print("  - task2_noise_analysis.png")
    print("  - task2_transmission_power_analysis.png")
    print("  - task2_sensitivity_analysis.png")
    print("  - task2_ber_snir_comprehensive_analysis.png")
    print("  - task2_comprehensive_summary.csv")

if __name__ == "__main__":
    main() 