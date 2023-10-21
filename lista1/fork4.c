#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t c1;
    pid_t c2 = 0;

    c1 = fork(); /* fork numero 1 */
    if(c1 == 0)
        c2 = fork(); /* fork numero 2 */
    fork(); /* fork numero 3 */
    if(c2 > 0)
        fork(); /* fork numero 4 */

    return 0;
}
