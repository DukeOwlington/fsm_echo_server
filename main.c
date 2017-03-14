#include "server_routine.h"
#include "fsm.h"

int main(void) {
  STATE state = STATE_TURNED_OFF;
  /* initialize server */
  EVENT evt = EVENT_INITIALIZE;

  if (trans_tbl[evt][state].action() < 0)
    return EXIT_FAILURE;

  state = trans_tbl[evt][state].next_state;

  /* keep listening for data */
  while (evt != EVENT_TURN_OFF) {
    evt = EVENT_RECEIVE;
    if (trans_tbl[evt][state].action() < 0)
      return EXIT_FAILURE;
    state = trans_tbl[evt][state].next_state;

    evt = EVENT_SEND;
    if (trans_tbl[evt][state].action() < 0)
      return EXIT_FAILURE;
    state = trans_tbl[evt][state].next_state;
  }

  return 0;
}
