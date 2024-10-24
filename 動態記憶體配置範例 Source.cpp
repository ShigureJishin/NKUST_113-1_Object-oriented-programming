#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 128
struct sPERSON {
	char name[12888];
	int age;
	float height;
};

typedef struct sPERSON Person;

int main() {
	Person *p_list[MAXLEN];
	int idx_plist = 0;
	int i;
	Person *tmp;
	for (i = 0; i < MAXLEN; i++)
		p_list[i] = NULL;

	int conti = 1;
	scanf("%d", &conti);
	while (conti == 1) {
		idx_plist = 0;
		for (i = 0; i < 100; i++) {
			tmp = (Person *)malloc(sizeof(Person));
			sprintf(tmp->name, "Bob%d", i);
			tmp->age = 10;
			tmp->height = 99.8;
			p_list[idx_plist] = tmp;
			idx_plist++;
		}
		scanf("%d", &conti);
		if (conti == 1) {
			for (i = 0; i < idx_plist; i++) {
				free(p_list[i]);
				p_list[i] = NULL;
			}
		}
	}
	
	
	for (i = 0; i < idx_plist; i++) {
		tmp = p_list[i];
		printf("%s %d %f\n", tmp->name, tmp->age, tmp->height);
	}


	system("pause");
}