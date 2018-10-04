
void setup_relays();
uint8_t loop_relays(uint8_t system_state);
void set_input(uint8_t input);

uint8_t get_current_input();
void advance_input();
void turn_relay_off(uint8_t rel);
void turn_relay_on(uint8_t rel);
void turn_all_relays_off();