#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAX_SENTENCE_LENGTH 100
#define NUM_SENTENCES 15

const char* sentences[NUM_SENTENCES] = {
    "java�� ���� �ڹ�.",
    "�ѱ��� �Ƹ��ٿ� ����Դϴ�.",
    "���α׷����� ����ֽ��ϴ�.",
    "C ���� ������ ���α׷��� ����Դϴ�.",
    "��ǻ�� ������ ��̷ο� �о��Դϴ�.",
    "�ڵ�� ��� �����̴� �����̴�.",
    "� ������ �ذ��� �� �ִ� ����� �����Ѵ�",
    "�ڵ�� �� ���� �����ڸ� �����.",
    "���� �ڵ�� ���� �������� ����. �׷��� ���� ���� ���� ���� �ڵ�� ����.",
    "���� ����� ���׸� ã�� ���ߴٸ�, ����� ���� ����� ã�� ���� ���̴�.",
    "���� ���� ���α׷��Ӵ� �׵��� �� �ڵ带 �ִ��� ª�� �����ϴ� ����̴�.",
    "�ڵ带 �� ���� ����� �����ϱ� ������ �ۼ��϶�.",
    "���� ���α׷����� �Ǹ��� ���丮�ڸ��� ����. �����ϰ� ��Ȯ�ؾ� �Ѵ�.",
    "�ڵ��� ����� �����̴�.",
    "� ���� ������ ���� ����� �ڵ尡 �ƴ϶� �װ��� �ϴ� ���̴�."
};

void clear_terminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void typing_test_1() {
    srand(time(NULL));
    time_t start_time, current_time;
    char input_text[MAX_SENTENCE_LENGTH];
    int correct_entries = 0;

    time(&start_time);
    current_time = start_time;

    while (difftime(current_time, start_time) < 30) {
        int sentence_index = rand() % NUM_SENTENCES;
        const char* test_sentence = sentences[sentence_index];

        printf("���� ������ �Է��ϼ���:\n%s\n", test_sentence);

        printf("�Է� ��� ��... (���� �ð�: %d��)\n", 30 - (int)difftime(current_time, start_time));
        fflush(stdout);

        // �Է� ��� ����
        int retval = 0;
        while (retval == 0 && difftime(current_time, start_time) < 30) {
            if (_kbhit()) {
                fgets(input_text, MAX_SENTENCE_LENGTH, stdin);
                retval = 1;
            }
            else {
                Sleep(100); // 100�и��� ���
            }
            time(&current_time);
        }

        if (retval) {
            // �Է��� ������ ���� �ִ� '\n' ����
            size_t len = strlen(input_text);
            if (len > 0 && input_text[len - 1] == '\n') {
                input_text[len - 1] = '\0';
            }

            if (strcmp(input_text, test_sentence) == 0) {
                correct_entries++;
                printf("��Ȯ�ϰ� �Է��߽��ϴ�.\n");
            }
            else {
                printf("�߸� �Է��߽��ϴ�. �ٽ� �õ��ϼ���.\n");
            }
        }
        else {
            printf("�ð� �ʰ�!\n");
            break;
        }

        time(&current_time);
        int remaining_time = 30 - (int)difftime(current_time, start_time);
        printf("���� �ð�: %d��\n", remaining_time);
        fflush(stdout);

        if (remaining_time <= 0) {
            printf("�ð� �ʰ�!\n");
            break;
        }
    }

    printf("30�� ���� �ùٸ��� �Է��� Ƚ��: %d\n", correct_entries);

    printf("\n");
    system("pause");
}

void typing_test_2() {
    srand(time(NULL));
    int sentence_index = rand() % NUM_SENTENCES;
    const char* test_sentence = sentences[sentence_index];

    char input_text[MAX_SENTENCE_LENGTH];
    time_t start_time, end_time;

    printf("�Է��� ����: %s\n", test_sentence);

    time(&start_time);
    printf("������ �Է��ϰ� ���͸� ��������: ");
    fgets(input_text, MAX_SENTENCE_LENGTH, stdin);
    time(&end_time);

    // �Է��� ������ ���� �ִ� '\n' ����
    size_t len = strlen(input_text);
    if (len > 0 && input_text[len - 1] == '\n') {
        input_text[len - 1] = '\0';
    }

    double elapsed_time = difftime(end_time, start_time);
    int correct_chars = 0;
    for (int i = 0; i < strlen(test_sentence); i++) {
        if (input_text[i] == test_sentence[i]) {
            correct_chars++;
        }
    }
    double accuracy = (double)correct_chars / strlen(test_sentence) * 100.0;

    printf("�Է� �ð�: %.2f��\n", elapsed_time);
    printf("��Ȯ��: %.2f%%\n", accuracy);
    printf("�ӵ�: %.2f chars/sec\n", strlen(input_text) / elapsed_time);

    printf("\n");
    system("pause");
}

int main() {
    printf("       �������� ����Ÿ�ڿ���\n");

    while (1) {
        int choice;

        printf("     --------------------------\n");

        printf("     1. 30�� Ÿ���� �׽�Ʈ\n");
        printf("     2. ���� Ÿ���� �׽�Ʈ\n");
        printf("     3. ����ũ ������\n");
        printf("     4. �ػ� ����\n");
        printf("     5. ����� ���\n");
        printf("     6. ������ ��Ʈ\n");
        printf("     7. ���α׷� ����\n");

        printf("     --------------------------\n");
        printf("     �����ϼ���: ");
        scanf("%d", &choice);
        getchar();  // '\n' ���ڸ� ����

        switch (choice) {
        case 1:
            clear_terminal();
            typing_test_1();
            clear_terminal();
            break;
        case 2:
            clear_terminal();
            typing_test_2();
            clear_terminal();
            break;
        case 3:
            printf("     ���� �� �Դϴ�. �ٽ� �����ϼ���.\n");
            break;
        case 4:
            printf("     ���� �� �Դϴ�. �ٽ� �����ϼ���.\n");
            break;
        case 5:
            printf("     ���� �� �Դϴ�. �ٽ� �����ϼ���.\n");
            break;
        case 6:
            printf("     �ۼ� �� �Դϴ�. �ٽ� �����ϼ���.\n");
            break;
        case 7:
            printf("     ���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("     �߸��� �����Դϴ�. �ٽ� �����ϼ���.\n");
            break;
        }
    }

    return 0;
}
