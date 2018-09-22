#include "pattern.hpp"

void add_pulsar(Cell *cells, bool *cell_states, int center) {
    int pulsar[48];
    if ((center % X_CELLS > 7) &&
        (center % X_CELLS < X_CELLS - 8) &&
        (center / X_CELLS > 7) &&
        (center / X_CELLS < Y_CELLS - 8)) {
            int counter = 0;
            pulsar[counter++] = center - X_CELLS - 2;
            pulsar[counter++] = center - X_CELLS - 3;
            pulsar[counter++] = center - X_CELLS - 4;
            pulsar[counter++] = center - X_CELLS + 2;
            pulsar[counter++] = center - X_CELLS + 3;
            pulsar[counter++] = center - X_CELLS + 4;
            pulsar[counter++] = center + X_CELLS - 2;
            pulsar[counter++] = center + X_CELLS - 3;
            pulsar[counter++] = center + X_CELLS - 4;
            pulsar[counter++] = center + X_CELLS + 2;
            pulsar[counter++] = center + X_CELLS + 3;
            pulsar[counter++] = center + X_CELLS + 4;

            pulsar[counter++] = center - X_CELLS * 2 - 1;
            pulsar[counter++] = center - X_CELLS * 3 - 1;
            pulsar[counter++] = center - X_CELLS * 4 - 1;
            pulsar[counter++] = center - X_CELLS * 2 + 1;
            pulsar[counter++] = center - X_CELLS * 3 + 1;
            pulsar[counter++] = center - X_CELLS * 4 + 1;
            pulsar[counter++] = center + X_CELLS * 2 - 1;
            pulsar[counter++] = center + X_CELLS * 3 - 1;
            pulsar[counter++] = center + X_CELLS * 4 - 1;
            pulsar[counter++] = center + X_CELLS * 2 + 1;
            pulsar[counter++] = center + X_CELLS * 3 + 1;
            pulsar[counter++] = center + X_CELLS * 4 + 1;
            for (int i = 0; i < 24; ++i)
            {
                cell_states[pulsar[i]] = true;
                cells[pulsar[i]].make_alive();
                cells[pulsar[i]].make_active();
            }
    }
    return;
}