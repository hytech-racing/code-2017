#ifndef __HYTECH17_H__
#define __HYTECH17_H__

#include <string.h>
#include <stdint.h>

/*
 * ECU state definitions
 */
#define PCU_STATE_WAITING_BMS_IMD 1
#define PCU_STATE_WAITING_DRIVER 2
#define PCU_STATE_LATCHING 3
#define PCU_STATE_SHUTDOWN_CIRCUIT_INITIALIZED 4
#define PCU_STATE_FATAL_FAULT 5
#define TCU_STATE_WAITING_SHUTDOWN_CIRCUIT_INITIALIZED 1
#define TCU_STATE_WAITING_TRACTIVE_SYSTEM 2
#define TCU_STATE_TRACTIVE_SYSTEM_NOT_ACTIVE 3
#define TCU_STATE_TRACTIVE_SYSTEM_ACTIVE 4
#define TCU_STATE_ENABLING_INVERTER 5
#define TCU_STATE_WAITING_READY_TO_DRIVE_SOUND 6
#define TCU_STATE_READY_TO_DRIVE 7

/*
 * CAN ID definitions
 */
#define ID_PCU_STATUS 0xD0
#define ID_TCU_STATUS 0xD1
#define ID_MC_TEMPERATURES_1 0xA0
#define ID_MC_TEMPERATURES_2 0xA1
#define ID_MC_TEMPERATURES_3 0xA2
#define ID_MC_ANALOG_INPUTS_VOLTAGES 0xA3
#define ID_MC_DIGITAL_INPUT_STATUS 0xA4
#define ID_MC_MOTOR_POSITION_INFORMATION 0xA5
#define ID_MC_CURRENT_INFORMATION 0xA6
#define ID_MC_VOLTAGE_INFORMATION 0xA7
#define ID_MC_FLUX_INFORMATION 0xA8
#define ID_MC_INTERNAL_VOLTAGES 0xA9
#define ID_MC_INTERNAL_STATES 0xAA
#define ID_MC_FAULT_CODES 0xAB
#define ID_MC_TORQUE_TIMER_INFORMATION 0xAC
#define ID_MC_MODULATION_INDEX_FLUX_WEAKENING_OUTPUT_INFORMATION 0xAD
#define ID_MC_FIRMWARE_INFORMATION 0xAE
#define ID_MC_DIAGNOSTIC_DATA 0xAF
#define ID_MC_COMMAND_MESSAGE 0xC0
#define ID_MC_READ_WRITE_PARAMETER_COMMAND 0xC1
#define ID_MC_READ_WRITE_PARAMETER_RESPONSE 0xC2

/*
 * CAN message structs and classes
 */
typedef struct CAN_message_pcu_status_t {
  uint8_t state;
  bool bms_fault;
  bool imd_fault;
} CAN_msg_pcu_status;

class PCU_status {
  public:
    PCU_status();
    PCU_status(uint8_t buf[8]);
    PCU_status(uint8_t state, bool bms_fault, bool imd_fault);
    void load(uint8_t buf[8]);
    void write(uint8_t buf[8]);
    uint8_t get_state();
    bool get_bms_fault();
    bool get_imd_fault();
    void set_state(uint8_t state);
    void set_bms_fault(bool bms_fault);
    void set_imd_fault(bool imd_fault);
  private:
    CAN_message_pcu_status_t message;
};

typedef struct CAN_message_tcu_status_t {
  uint8_t state;
  uint8_t btn_start_id;
} CAN_msg_tcu_status;

class TCU_status {
  public:
    TCU_status();
    TCU_status(uint8_t buf[8]);
    TCU_status(uint8_t state, uint8_t btn_start_id);
    void load(uint8_t buf[8]);
    void write(uint8_t buf[8]);
    uint8_t get_state();
    uint8_t get_btn_start_id();
    void set_state(uint8_t state);
    void set_btn_start_id(uint8_t btn_start_id);
  private:
    CAN_message_tcu_status_t message;
};

typedef struct CAN_message_mc_temperatures_1_t {
  int16_t module_a_temperature;
  int16_t module_b_temperature;
  int16_t module_c_temperature;
  int16_t gate_driver_board_temperature;
} CAN_message_mc_temperatures_1_t;

class MC_temperatures_1 {
  public:
    MC_temperatures_1();
    MC_temperatures_1(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    int16_t get_module_a_temperature();
    int16_t get_module_b_temperature();
    int16_t get_module_c_temperature();
    int16_t get_gate_driver_board_temperature();
  private:
    CAN_message_mc_temperatures_1_t message;
};

typedef struct CAN_message_mc_temperatures_2_t {
  int16_t control_board_temperature;
  int16_t rtd_1_temperature;
  int16_t rtd_2_temperature;
  int16_t rtd_3_temperature;
} CAN_message_mc_temperatures_2_t;

class MC_temperatures_2 {
  public:
    MC_temperatures_2();
    MC_temperatures_2(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    int16_t get_control_board_temperature();
    int16_t get_rtd_1_temperature();
    int16_t get_rtd_2_temperature();
    int16_t get_rtd_3_temperature();
  private:
    CAN_message_mc_temperatures_2_t message;
};

typedef struct CAN_message_mc_temperatures_3_t {
  int16_t rtd_4_temperature;
  int16_t rtd_5_temperature;
  int16_t motor_temperature;
  int16_t torque_shudder;
} CAN_message_mc_temperatures_3_t;

class MC_temperatures_3 {
  public:
    MC_temperatures_3();
    MC_temperatures_3(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    int16_t get_rtd_4_temperature();
    int16_t get_rtd_5_temperature();
    int16_t get_motor_temperature();
    int16_t get_torque_shudder();
  private:
    CAN_message_mc_temperatures_3_t message;
};

typedef struct CAN_message_mc_analog_input_voltages_t {
  int16_t analog_input_1;
  int16_t analog_input_2;
  int16_t analog_input_3;
  int16_t analog_input_4;
} CAN_message_mc_analog_input_voltages_t;

class MC_analog_input_voltages {
  public:
    MC_analog_input_voltages();
    MC_analog_input_voltages(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    int16_t get_analog_input_1();
    int16_t get_analog_input_2();
    int16_t get_analog_input_3();
    int16_t get_analog_input_4();
  private:
    CAN_message_mc_analog_input_voltages_t message;
};

typedef struct CAN_message_mc_digital_input_status_t {
  bool digital_input_1;
  bool digital_input_2;
  bool digital_input_3;
  bool digital_input_4;
  bool digital_input_5;
  bool digital_input_6;
  bool digital_input_7;
  bool digital_input_8;
} CAN_message_mc_digital_input_status_t;

class MC_digital_input_status {
  public:
    MC_digital_input_status();
    MC_digital_input_status(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    bool digital_input_1();
    bool digital_input_2();
    bool digital_input_3();
    bool digital_input_4();
    bool digital_input_5();
    bool digital_input_6();
    bool digital_input_7();
    bool digital_input_8();
  private:
    CAN_message_mc_digital_input_status_t message;
};

typedef struct CAN_message_mc_motor_position_information_t {
  int16_t motor_angle;
  int16_t motor_speed;
  int16_t electrical_output_frequency;
  int16_t delta_resolver_filtered;
} CAN_message_mc_motor_position_information_t;

class MC_motor_position_information {
  public:
    MC_motor_position_information();
    MC_motor_position_information(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    int16_t get_motor_angle();
    int16_t get_motor_speed();
    int16_t get_electrical_output_frequency();
    int16_t get_delta_resolver_filtered();
  private:
    CAN_message_mc_motor_position_information_t message;
};

typedef struct CAN_message_mc_current_information_t {
  int16_t phase_a_current;
  int16_t phase_b_current;
  int16_t phase_c_current;
  int16_t dc_bus_current;
} CAN_message_mc_current_information_t;

class MC_current_information {
  public:
    MC_current_information();
    MC_current_information(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    int16_t get_phase_a_current();
    int16_t get_phase_b_current();
    int16_t get_phase_c_current();
    int16_t get_dc_bus_current();
  private:
    CAN_message_mc_current_information_t message;
};

typedef struct CAN_message_mc_voltage_information_t {
  int16_t dc_bus_voltage;
  int16_t output_voltage;
  int16_t phase_ab_voltage;
  int16_t phase_bc_voltage;
} CAN_message_mc_voltage_information_t;

class MC_voltage_information {
  public:
    MC_voltage_information();
    MC_voltage_information(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    int16_t get_dc_bus_voltage();
    int16_t get_output_voltage();
    int16_t get_phase_ab_voltage();
    int16_t get_phase_bc_voltage();
  private:
    CAN_message_mc_voltage_information_t message;
};

typedef struct CAN_message_mc_internal_states_t {
  uint16_t vsm_state;
  uint8_t inverter_state;
  uint8_t relay_state;
  uint8_t inverter_run_mode_discharge_state;
  uint8_t inverter_command_mode;
  uint8_t inverter_enable;
  uint8_t direction_command;
} CAN_message_mc_internal_states_t;

class MC_internal_states {
  public:
    MC_internal_states();
    MC_internal_states(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    uint8_t get_vsm_state();
    uint8_t get_inverter_state();
    bool get_relay_active_1();
    bool get_relay_active_2();
    bool get_relay_active_3();
    bool get_relay_active_4();
    bool get_relay_active_5();
    bool get_relay_active_6();
    bool get_inverter_run_mode();
    uint8_t get_inverter_active_discharge_state();
    bool get_inverter_command_mode();
    bool get_inverter_enable_state();
    bool get_inverter_enable_lockout();
    bool get_direction_command();
  private:
    CAN_message_mc_internal_states_t message;
};

typedef struct CAN_message_mc_fault_codes_t {
  uint16_t post_fault_lo;
  uint16_t post_fault_hi;
  uint16_t run_fault_lo;
  uint16_t run_fault_hi;
} CAN_message_mc_fault_codes_t;

class MC_fault_codes {
  public:
    MC_fault_codes();
    MC_fault_codes(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    bool get_post_lo_hw_gate_desaturation_fault();
    bool get_post_lo_hw_overcurrent_fault();
    bool get_post_lo_accelerator_shorted();
    bool get_post_lo_accelerator_open();
    bool get_post_lo_current_sensor_low();
    bool get_post_lo_current_sensor_high();
    bool get_post_lo_module_temperature_low();
    bool get_post_lo_module_temperature_high();
    bool get_post_lo_ctrl_pcb_temperature_low();
    bool get_post_lo_ctrl_pcb_temperature_high();
    bool get_post_lo_gate_drive_pcb_temperature_low();
    bool get_post_lo_gate_drive_pcb_temperature_high();
    bool get_post_lo_5v_sense_voltage_low();
    bool get_post_lo_5v_sense_voltage_high();
    bool get_post_lo_12v_sense_voltage_low();
    bool get_post_lo_12v_sense_voltage_high();
    bool get_post_hi_25v_sense_voltage_low();
    bool get_post_hi_25v_sense_voltage_high();
    bool get_post_hi_15v_sense_voltage_low();
    bool get_post_hi_15v_sense_voltage_high();
    bool get_post_hi_dc_bus_voltage_high();
    bool get_post_hi_dc_bus_voltage_low();
    bool get_post_hi_precharge_timeout();
    bool get_post_hi_precharge_voltage_failure();
    bool get_post_hi_eeprom_checksum_invalid();
    bool get_post_hi_eeprom_data_out_of_range();
    bool get_post_hi_eeprom_update_required();
    bool get_post_hi_reserved1(); // TODO delete these?
    bool get_post_hi_reserved2();
    bool get_post_hi_reserved3();
    bool get_post_hi_brake_shorted();
    bool get_post_hi_brake_open();
    bool get_run_lo_motor_overspeed_fault();
    bool get_run_lo_overcurrent_fault();
    bool get_run_lo_overvoltage_fault();
    bool get_run_lo_inverter_overtemperature_fault();
    bool get_run_lo_accelerator_input_shorted_fault();
    bool get_run_lo_accelerator_input_open_fault();
    bool get_run_lo_direction_command_fault();
    bool get_run_lo_inverter_response_timeout_fault();
    bool get_run_lo_hardware_gatedesaturation_fault();
    bool get_run_lo_hardware_overcurrent_fault();
    bool get_run_lo_undervoltage_fault();
    bool get_run_lo_can_command_message_lost_fault();
    bool get_run_lo_motor_overtemperature_fault();
    bool get_run_lo_reserved1(); // TODO delete these?
    bool get_run_lo_reserved2();
    bool get_run_lo_reserved3();
    bool get_run_hi_brake_input_shorted_fault();
    bool get_run_hi_brake_input_open_fault();
    bool get_run_hi_module_a_overtemperature_fault();
    bool get_run_hi_module_b_overtemperature_fault();
    bool get_run_hi_module_c_overtemperature_fault();
    bool get_run_hi_pcb_overtemperature_fault();
    bool get_run_hi_gate_drive_board_1_overtemperature_fault();
    bool get_run_hi_gate_drive_board_2_overtemperature_fault();
    bool get_run_hi_gate_drive_board_3_overtemperature_fault();
    bool get_run_hi_current_sensor_fault();
    bool get_run_hi_reserved1(); // TODO delete these?
    bool get_run_hi_reserved2();
    bool get_run_hi_reserved3();
    bool get_run_hi_reserved4();
    bool get_run_hi_resolved_not_connected();
    bool get_run_hi_inverter_discharge_active();
  private:
    CAN_message_mc_fault_codes_t message;
};

typedef struct CAN_message_mc_torque_timer_information_t {
  int16_t commanded_torque;
  int16_t torque_feedback;
  uint32_t power_on_timer;
} CAN_message_mc_torque_timer_information_t;

class MC_torque_timer_information {
  public:
    MC_torque_timer_information();
    MC_torque_timer_information(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    int16_t get_commanded_torque();
    int16_t get_torque_feedback();
    uint32_t get_power_on_timer();
  private:
    CAN_message_mc_torque_timer_information_t message;
};

typedef struct CAN_message_mc_modulation_index_flux_weakening_output_information_t {
  uint16_t modulation_index; // TODO Signed or Unsigned?
  int16_t flux_weakening_output;
  int16_t id_command;
  int16_t iq_command;
} CAN_message_mc_modulation_index_flux_weakening_output_information_t;

class MC_modulation_index_flux_weakening_output_information {
  public:
    MC_modulation_index_flux_weakening_output_information();
    MC_modulation_index_flux_weakening_output_information(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    uint16_t get_modulation_index();
    int16_t get_flux_weakening_output();
    int16_t get_id_command();
    int16_t get_iq_command();
  private:
    CAN_message_mc_modulation_index_flux_weakening_output_information_t message;
};

typedef struct CAN_message_mc_firmware_information_t {
  uint16_t eeprom_version_project_code;
  uint16_t software_version;
  uint16_t date_code_mmdd;
  uint16_t date_code_yyyy;
} CAN_message_mc_firmware_information_t;

class MC_firmware_information {
  public:
    MC_firmware_information();
    MC_firmware_information(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    uint16_t get_eeprom_version_project_code();
    uint16_t get_software_version();
    uint16_t get_date_code_mmdd();
    uint16_t get_date_code_yyyy();
  private:
    CAN_message_mc_firmware_information_t message;
};

typedef struct CAN_message_mc_command_message_t {
  int16_t torque_command;
  int16_t angular_velocity;
  bool direction;
  uint8_t inverter_enable_discharge_enable;
  int16_t commanded_torque_limit;
} CAN_message_mc_command_message_t;

class MC_command_message {
  public:
    MC_command_message();
    MC_command_message(uint8_t buf[8]);
    MC_command_message(int16_t torque_command, int16_t angular_velocity, bool direction, bool inverter_enable, bool discharge_enable, int16_t commanded_torque_limit);
    void load(uint8_t buf[8]);
    void write(uint8_t buf[8]);
    int16_t get_torque_command();
    int16_t get_angular_velocity();
    bool get_direction();
    bool get_inverter_enable();
    bool get_discharge_enable();
    int16_t get_commanded_torque_limit();
    void set_torque_command(int16_t torque_command);
    void set_angular_velocity(int16_t angular_velocity);
    void set_direction(bool direction);
    void set_inverter_enable(bool inverter_enable);
    void set_discharge_enable(bool discharge_enable);
    void set_commanded_torque_limit(int16_t commanded_torque_limit);
  private:
    CAN_message_mc_command_message_t message;
};

typedef struct CAN_message_mc_read_write_parameter_command_t {
  uint16_t parameter_address;
  bool rw_command;
  uint8_t reserved1;
  uint16_t data;
  uint16_t reserved2;
} CAN_message_mc_read_write_parameter_command_t;

class MC_read_write_parameter_command {
  public:
    MC_read_write_parameter_command();
    MC_read_write_parameter_command(uint8_t buf[8]);
    MC_read_write_parameter_command(uint16_t parameter_address, bool rw_command, uint16_t data);
    void load(uint8_t buf[8]);
    void write(uint8_t buf[8]);
    uint16_t get_parameter_address();
    bool get_rw_command();
    uint16_t get_data();
    void set_parameter_address(uint16_t parameter_address);
    void set_rw_command(bool rw_command);
    void set_data(uint16_t data);
  private:
    CAN_message_mc_read_write_parameter_command_t message;
};

typedef struct CAN_message_mc_read_write_parameter_response_t {
  uint16_t parameter_address;
  bool write_success;
  uint8_t reserved1;
  uint16_t data;
  uint16_t reserved2;
} CAN_message_mc_read_write_parameter_response_t;

class MC_read_write_parameter_response {
  public:
    MC_read_write_parameter_response();
    MC_read_write_parameter_response(uint8_t buf[8]);
    void load(uint8_t buf[8]);
    uint16_t get_parameter_address();
    bool get_write_success();
    uint16_t get_data();
  private:
    CAN_message_mc_read_write_parameter_response_t message;
};

#endif