#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAX_SENTENCE_LENGTH 100
#define NUM_SENTENCES 15
#define WORD_COUNT 100
#define GRID_SIZE 16
#define DISPLAY_TIME 5
#define MAX_NAME_LENGTH 50
#define RANKING_FILE "ranking.txt"

void generate_random_words(char words[WORD_COUNT][20]);
void shuffle_words(char words[WORD_COUNT][20]);
void display_grid(char grid[GRID_SIZE][20]);
void hide_grid();
int is_word_in_grid(char grid[GRID_SIZE][20], char* word, int* remaining);
void update_ranking(const char* name, int score);
void show_ranking();

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

void generate_random_words(char words[WORD_COUNT][20]) {
    const char* sample_words[WORD_COUNT] = {
        "���", "�ٳ���", "ü��", "����", "��������", "��ȭ��", "����", "��ϵ�",
        "Ű��", "����", "����", "��Ÿ��", "������", "���ľ�", "���", "�����",
        "����", "��", "��۸�", "�ٴҶ�", "����", "����", "Ȳ�ݿ���", "ȣ��",
        "�챸", "������", "���", "���", "��������Ʈ", "��������", "�ڸ�",
        "��Ŭ����", "�Ӻ�", "������Ʈ", "�ݱ�", "����", "���", "��Ÿ", "�ø���",
        "������", "��ƶ󸮺���", "�ο�", "���ƹ�", "�丶��", "���", "���ƹ氡",
        "��������", "�ڸ�", "����", "�ڵ�", "��", "��", "�Ž�", "���", "�ڵ�",
        "�챸", "����", "������", "�챸", "�ٷ�", "�ڵ�", "����", "��", "���ٷ�",
        "����", "����", "�丶��", "���ٷ�", "�ڵ�", "��", "��", "�ٷ�", "����",
        "���ٷ�", "����", "����", "������", "��", "����", "����", "����", "������",
        "�챸", "�ڵ�", "�Ž�", "�ڵ�", "��", "�ٷ�", "���ٷ�", "������", "�ڵ�",
        "����", "����", "������", "�Ž�", "�ڵ�", "�ٷ�", "����", "����", "�ٷ�"
    };

    for (int i = 0; i < WORD_COUNT; i++) {
        strcpy(words[i], sample_words[i]);
    }
}

void shuffle_words(char words[WORD_COUNT][20]) {
    srand((unsigned int)time(NULL));
    for (int i = WORD_COUNT - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[20];
        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
    }
}

void display_grid(char grid[GRID_SIZE][20]) {
    printf("�ܾ� �׸���:\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%s ", grid[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
}

void hide_grid() {
    system("cls");
    printf("5�ʰ� ���� �׸��尡 ���������ϴ�.\n");
}

int is_word_in_grid(char grid[GRID_SIZE][20], char* word, int* remaining) {
    for (int i = 0; i < GRID_SIZE; i++) {
        if (strcmp(grid[i], word) == 0) {
            strcpy(grid[i], "");  // �ܾ ������ �� �� ���ڿ��� �ٲ㼭 �ٽ� ������ ���ϰ� ��
            (*remaining)--;
            return 1;
        }
    }
    return 0;
}

void update_ranking(const char* name, int score) {
    FILE* file = fopen(RANKING_FILE, "a+");
    if (file == NULL) {
        printf("��ŷ ������ �� �� �����ϴ�.\n");
        return;
    }

    char line[100];
    char player_name[MAX_NAME_LENGTH];
    int player_score;
    int found = 0;

    FILE* temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("�ӽ� ������ ������ �� �����ϴ�.\n");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %d", player_name, &player_score);
        if (strcmp(player_name, name) == 0) {
            if (score > player_score) {
                fprintf(temp_file, "%s %d\n", name, score);
            }
            else {
                fprintf(temp_file, "%s %d\n", player_name, player_score);
            }
            found = 1;
        }
        else {
            fprintf(temp_file, "%s %d\n", player_name, player_score);
        }
    }

    if (!found) {
        fprintf(temp_file, "%s %d\n", name, score);
    }

    fclose(file);
    fclose(temp_file);

    remove(RANKING_FILE);
    rename("temp.txt", RANKING_FILE);
}

void show_ranking() {
    FILE* file = fopen(RANKING_FILE, "r");
    if (file == NULL) {
        printf("��ŷ ������ �� �� �����ϴ�.\n");
        return;
    }

    char line[100];
    printf("��ü ��ŷ:\n");
    printf("------------\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void clear_terminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void typing_test_1(const char* nickname) {
    srand(time(NULL));
    time_t start_time, current_time;
    char input_text[MAX_SENTENCE_LENGTH];
    int correct_entries = 0;

    time(&start_time);
    current_time = start_time;

    while (difftime(current_time, start_time) < 30) {
        int sentence_index = rand() % NUM_SENTENCES;
        const char* test_sentence = sentences[sentence_index];

        printf("���� ������ �Է��ϼ���:\n\033[30m\033[47m%s\n\033[0m", test_sentence);

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
                printf("��Ȯ�ϰ� �Է��߽��ϴ�.\n\n");
            }
            else {
                printf("�߸� �Է��߽��ϴ�. �ٽ� �õ��ϼ���.\n\n");
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

    // ������ �б� ���� ����
    FILE* fp = fopen("rankings.txt", "r");
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // ���� ��Ʈ�� ����ü ����
    typedef struct {
        char nickname[50];
        int correct_entries;
    } Entry;

    Entry entries[NUM_SENTENCES];
    int num_entries = 0;

    // ���Ͽ��� ��Ʈ�� �о����
    while (fscanf(fp, "%s\t%d\n", entries[num_entries].nickname, &entries[num_entries].correct_entries) != EOF) {
        num_entries++;
    }

    fclose(fp);

    // ���� ���� �˻� �� ���� ������Ʈ
    int nickname_found = 0;
    for (int i = 0; i < num_entries; i++) {
        if (strcmp(entries[i].nickname, nickname) == 0) {
            if (entries[i].correct_entries < correct_entries) {
                entries[i].correct_entries = correct_entries;
            }
            nickname_found = 1;
            break;
        }
    }

    // ���ο� �����̸� ��Ʈ���� �߰�
    if (!nickname_found) {
        strcpy(entries[num_entries].nickname, nickname);
        entries[num_entries].correct_entries = correct_entries;
        num_entries++;
    }

    // ������ ���� ���� ����
    fp = fopen("rankings.txt", "w");
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // ���Ͽ� ��Ʈ�� ����
    for (int i = 0; i < num_entries; i++) {
        fprintf(fp, "%s\t%d\n", entries[i].nickname, entries[i].correct_entries);
    }

    fclose(fp);

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

void view_rankings() {
    FILE* fp = fopen("rankings.txt", "r");
    if (fp == NULL) {
        printf("��ŷ ������ �� �� �����ϴ�.\n");
        return;
    }

    printf("\n��ü ��ŷ:\n");
    printf("------------\n");

    // ��Ʈ�� ����ü ����
    typedef struct {
        char nickname[50];
        int correct_entries;
    } Entry;

    Entry entries[NUM_SENTENCES];
    int num_entries = 0;

    // ���Ͽ��� ��Ʈ�� �о����
    while (fscanf(fp, "%s\t%d\n", entries[num_entries].nickname, &entries[num_entries].correct_entries) != EOF) {
        num_entries++;
    }

    fclose(fp);

    // ��Ȯ�� �Է� Ƚ���� ���� �����ϱ� (��������)
    for (int i = 0; i < num_entries - 1; i++) {
        for (int j = i + 1; j < num_entries; j++) {
            if (entries[i].correct_entries < entries[j].correct_entries) {
                Entry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }

    // ���ĵ� ��Ʈ�� ����ϱ�
    for (int i = 0; i < num_entries; i++) {
        printf("%d��: %s - %d ��\n", i + 1, entries[i].nickname, entries[i].correct_entries);
    }

    printf("\n");
    system("pause");
}

void reset_rankings() {
    FILE* fp = fopen("rankings.txt", "w");
    if (fp == NULL) {
        printf("��ŷ ������ �� �� �����ϴ�.\n");
        return;
    }
    fclose(fp);
    printf("��ŷ�� �ʱ�ȭ�Ǿ����ϴ�.\n");
}

void reset_rankings2() {
    FILE* fp = fopen("ranking.txt", "w");
    if (fp == NULL) {
        printf("��ŷ ������ �� �� �����ϴ�.\n");
        return;
    }
    fclose(fp);
    printf("��ŷ�� �ʱ�ȭ�Ǿ����ϴ�.\n");
}

int main() {
    char words[WORD_COUNT][20];
    char grid[GRID_SIZE][20];
    char input[20];
    int score = 0;
    int choice;
    char nickname[50];

    while (1) {
        printf("       �������� ����Ÿ�ڿ���\n");
        system("pause");
        clear_terminal();

        printf("������ �Է��ϼ���: ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = '\0'; // ���� ���� ����

        clear_terminal();

        while (1) {
            int choice;

            printf("     ------�������� ����Ÿ��------\n");

            printf("     1. 30�� Ÿ���� �׽�Ʈ\n");
            printf("     2. ���� Ÿ���� �׽�Ʈ\n");
            printf("     3. �ܾ� ��� Ÿ���� ����\n");
            printf("     4. �ػ� ����\n");
            printf("     5. ����� ���\n");
            printf("     6. ������ ��Ʈ\n");
            printf("     7. ��ŷ ����\n");
            printf("     8. ������ ���\n");
            printf("     9. �α׾ƿ�\n");
            printf("     10. ���α׷� ����\n");

            printf("     --------------------------\n");
            printf("     �����ϼ���: ");
            scanf("%d", &choice);
            getchar();  // '\n' ���ڸ� ����

            switch (choice) {
                case 1:
                {
                    clear_terminal();
                    typing_test_1(nickname);
                    clear_terminal();
                    break;
                }
                case 2:
                {
                    clear_terminal();
                    typing_test_2();
                    clear_terminal();
                    break;
                }
                case 3:
                {
                    clear_terminal();
                    generate_random_words(words);
                    shuffle_words(words);

                    for (int i = 0; i < GRID_SIZE; i++) {
                        strcpy(grid[i], words[i]);
                    }

                    display_grid(grid);
                    Sleep(DISPLAY_TIME * 1000);
                    hide_grid();

                    int remaining = GRID_SIZE;

                    while (1) {
                        printf("�ܾ �Է��ϼ��� (���� �Է��ϸ� ����): ");
                        scanf("%s", input);

                        if (strcmp(input, "��") == 0) {
                            break;
                        }

                        if (is_word_in_grid(grid, input, &remaining)) {
                            printf("�¾ҽ��ϴ�!\n");
                            score++;
                            printf("���� �ܾ� ��: %d\n", remaining);
                        }
                        else {
                            printf("Ʋ�Ƚ��ϴ�.\n");
                        }
                    }
                    printf("���� ����! ����: %d\n", score);
                    update_ranking(nickname, score);
                    system("pause");
                    clear_terminal();
                    break;
                }
                case 4:
                {
                    clear_terminal();
                    printf("     ���� �� �Դϴ�. �ٽ� �����ϼ���.\n\n");
                    system("pause");
                    clear_terminal();
                    break;
                }
                case 5:
                {
                    clear_terminal();
                    printf("     ���� �� �Դϴ�. �ٽ� �����ϼ���.\n\n");
                    system("pause");
                    clear_terminal();
                    break;
                }
                case 6:
                {
                    clear_terminal();
                    printf("     ���� �� �Դϴ�. �ٽ� �����ϼ���.\n\n");
                    system("pause");
                    clear_terminal();
                    break;
                }
                case 10:
                {
                    printf("     ���α׷��� �����մϴ�.\n");
                    return 0;
                }
                case 7:
                {
                    clear_terminal();

                    int number;
                    printf("     --------------------------\n");
                    printf("     1. 30�� Ÿ���� �׽�Ʈ ��ŷ.\n");
                    printf("     2. �ܾ� ��� Ÿ���� ���� ��ŷ.\n");
                    printf("     --------------------------\n");
                    printf("     �����ϼ���: ");
                    scanf("%d", &number);
                    getchar();

                    switch (number) {
                    case 1:
                        clear_terminal();
                        view_rankings();
                        clear_terminal();
                        break;
                    case 2:
                        clear_terminal();
                        show_ranking();
                        system("pause");
                        clear_terminal();
                        break;
                    }
                    break;
                }
                case 8:
                {
                    clear_terminal();
                    char admin_password[20];
                    printf("������ ��й�ȣ�� �Է��ϼ���: ");
                    fgets(admin_password, sizeof(admin_password), stdin);
                    admin_password[strcspn(admin_password, "\n")] = '\0'; // ���� ���� ����

                    if (strcmp(admin_password, "abcd") == 0) {
                        clear_terminal();
                        int admin_choice;
                        printf("������ ��忡 �����Ͽ����ϴ�.\n");
                        printf("     --------------------------\n");
                        printf("     1.30�� Ÿ���� �׽�Ʈ ��ŷ �ʱ�ȭ\n");
                        printf("     2.�ܾ� ��� Ÿ���� ���� ��ŷ �ʱ�ȭ\n");
                        printf("     3. ���ư���\n");
                        printf("     --------------------------\n");
                        printf("     �����ϼ���: ");
                        scanf("%d", &admin_choice);
                        getchar();  // '\n' ���� ����

                        switch (admin_choice) {
                        case 1:
                            clear_terminal();
                            reset_rankings();
                            clear_terminal();
                            break;
                        case 3:
                            clear_terminal();
                            printf("������ ��忡�� ���ư��ϴ�.\n");
                            break;
                        case 2:
                            clear_terminal();
                            reset_rankings2();
                            clear_terminal();
                            break;
                        default:
                            printf("�߸��� �����Դϴ�. ������ ��带 �����մϴ�.\n");
                            break;
                        }
                    }
                    else {
                        printf("�߸��� ��й�ȣ�Դϴ�. ������ ��� ������ �źεǾ����ϴ�.\n");
                    }

                    system("pause");
                    clear_terminal();
                    break;
                }
                case 9:
                {
                    clear_terminal();
                    printf("�α׾ƿ��մϴ�.\n");
                    system("pause");
                    clear_terminal();
                    break;
                }
                default:
                {
                    clear_terminal();
                    printf("     �߸��� �����Դϴ�. �ٽ� �����ϼ���.\n");
                    system("pause");
                    clear_terminal();
                    break;
                }
                if (choice == 9) {
                    break; // �α׾ƿ��Ͽ� ������ �ٽ� �Է� �ޱ� ���� ���� while ���� Ż��
                }
            }
        }
    }
}
