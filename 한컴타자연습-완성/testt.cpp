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
#define ADMIN_PASSWORD "admin123"

void generate_random_words(char words[WORD_COUNT][20]);
void shuffle_words(char words[WORD_COUNT][20]);
void display_grid(char grid[GRID_SIZE][20]);
void hide_grid();
int is_word_in_grid(char grid[GRID_SIZE][20], char* word, int* remaining);
void update_ranking(const char* name, int score);
void show_ranking();
void typing_test(const char* nickname);
void word_game(const char* nickname);
void admin_mode();
void clear_terminal();

const char* sentences[NUM_SENTENCES] = {
    "java�� ���� �ڹ�.",
    "�ѱ��� �Ƹ��ٿ� ����Դϴ�.",
    "���α׷����� ����ֽ��ϴ�.",
    "C ���� ������ ���α׷��� ����Դϴ�.",
    "��ǻ�� ������ ��̷ο� �о��Դϴ�.",
    "�ڵ�� ��� �����̴� �����̴�.",
    "� ������ �ذ��� �� �ִ� ����� �����Ѵ�.",
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
    clear_terminal();
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
    printf("��ŷ:\n");
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

void typing_test(const char* nickname) {
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
                ("��Ȯ�մϴ�!\n");
            }
            else {
                printf("Ʋ�Ƚ��ϴ�. ������ \"%s\"�Դϴ�.\n", test_sentence);
            }
        }
    }

    printf("Ÿ���� �׽�Ʈ�� ����Ǿ����ϴ�.\n");
    printf("%s���� ��Ȯ�� �Է� Ƚ��: %d\n", nickname, correct_entries);
    update_ranking(nickname, correct_entries);
}

void word_game(const char* nickname) {
    char words[WORD_COUNT][20];
    char grid[GRID_SIZE][20];
    int remaining = GRID_SIZE;

    generate_random_words(words);
    shuffle_words(words);

    // �ܾ� �׸��� �ʱ�ȭ
    for (int i = 0; i < GRID_SIZE; i++) {
        strcpy(grid[i], words[i]);
    }

    printf("�ܾ� ������ �����մϴ�. �׸��尡 ǥ�õ˴ϴ�.\n");
    display_grid(grid);
    printf("5�� �Ŀ� �׸��尡 �������ϴ�.\n");

    Sleep(DISPLAY_TIME * 1000);  // 5�� ���

    hide_grid();

    time_t start_time, current_time;
    int correct_words = 0;

    time(&start_time);
    current_time = start_time;

    while (difftime(current_time, start_time) < 30 && remaining > 0) {
        char input_word[20];
        printf("�ܾ �Է��ϼ���: ");
        scanf("%s", input_word);

        if (is_word_in_grid(grid, input_word, &remaining)) {
            correct_words++;
            printf("�����Դϴ�!\n");
        }
        else {
            printf("Ʋ�Ƚ��ϴ�.\n");
        }

        time(&current_time);
    }

    printf("�ܾ� ������ ����Ǿ����ϴ�.\n");
    printf("%s���� ��Ȯ�� �ܾ� �Է� Ƚ��: %d\n", nickname, correct_words);
    update_ranking(nickname, correct_words);
}

void admin_mode() {
    printf("������ ��忡 �����ϼ̽��ϴ�.\n");
    printf("��й�ȣ�� �Է��ϼ���: ");

    char password[20];
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) == 0) {
        int choice;
        do {
            printf("\n=== ������ �޴� ===\n");
            printf("1. ��ŷ ����\n");
            printf("2. ��ŷ �ʱ�ȭ\n");
            printf("3. ���α׷� ����\n");
            printf("�޴��� �����ϼ���: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                show_ranking();
                break;
            case 2:
                remove(RANKING_FILE);
                printf("��ŷ�� �ʱ�ȭ�Ǿ����ϴ�.\n");
                break;
            case 3:
                printf("���α׷��� �����մϴ�.\n");
                exit(0);
            default:
                printf("�߸��� �����Դϴ�. �ٽ� �������ּ���.\n");
            }
        } while (choice != 3);
    }
    else {
        printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. ������ ��� ������ �źεǾ����ϴ�.\n");
    }
}

int main() {
    int menu_choice;
    char nickname[MAX_NAME_LENGTH];

    printf("ȯ���մϴ�! �г����� �Է��ϼ���: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = 0;  // '\n' ����

    do {
        printf("\n=== �޴� ===\n");
        printf("1. Ÿ���� �׽�Ʈ ����\n");
        printf("2. �ܾ� ���� ����\n");
        printf("3. ������ ���\n");
        printf("4. �α׾ƿ�\n");
        printf("5. ���α׷� ����\n");
        printf("�޴��� �����ϼ���: ");
        scanf("%d", &menu_choice);

        switch (menu_choice) {
        case 1:
            typing_test(nickname);
            break;
        case 2:
            word_game(nickname);
            break;
        case 3:
            admin_mode();
            break;
        case 4:
            printf("%s��, �α׾ƿ� �Ǿ����ϴ�.\n", nickname);
            break;
        case 5:
            printf("���α׷��� �����մϴ�.\n");
            exit(0);
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �������ּ���.\n");
        }
    } while (menu_choice != 4);

    return 0;
}

