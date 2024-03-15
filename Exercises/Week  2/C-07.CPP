#include <stdio.h>

int main() {
    for (int cur = 0, prev = 0; ;scanf("%d", &cur)) {
		if (cur < 0) {
			printf("%d", cur);
			break;
		}
		if (cur != prev) {
			printf("%d ", cur);
			prev = cur;
		}
	}
}