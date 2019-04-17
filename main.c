#include "header.h"

int main(int argc, char** argv)
{
    // convert student id from string to integer
    int student_id = atoi(argv[1]);

    char student_name[100];
    int student_section;

    // open student info file
    FILE* fp;
    fp = fopen("data//student_info.txt", "r");

    // read student info until it finds the student_id
    int index1 = 0;
    int index2 = 0;
    char buffer1[100];
    char buffer2[100];
    char buffer3[100];
    int temp;// = fscanf(fp, "%s %s %s\n", buffer1, buffer2, buffer3);
    while((temp = fscanf(fp, "%s %s %s\n", buffer1, buffer2, buffer3)) > 0)
    {
        if (student_id == atoi(buffer1))
        {
            strncpy(student_name, buffer2, strlen(buffer2));
            student_name[strlen(buffer2)] = 0.00;
            student_section = atoi(buffer3);
            break;
        }
        if ( atoi(buffer3) == 1 ) index1++;
        else index2++;
    }
    if ( (index1 >= 50) && (index2 >= 50) )
    {
        printf("There is no student with the student ID: %d\n", student_id);
        return 0;
    }
    fclose(fp);

    // (Mission 1)
    printf("Student ID: %d, Name: %s, Section Number: %d\n", 
            student_id, student_name, student_section);

    
    // open section score
    if (student_section == 1)
    {
        fp = fopen("data//scores_section1.dat", "r");
    }
    else
    {
        fp = fopen("data//scores_section2.dat", "r");
    }
    
    // read scores and copy values to int array
    const int num_sec_students = 50;
    int sec_scores[num_sec_students];
    fread(sec_scores, sizeof(int), num_sec_students, fp);
    fclose(fp);

    // calculate mean and standard deviation
    double sec_mean = calMean(sec_scores, num_sec_students);
    double sec_var = calVariance(sec_scores, num_sec_students);

    // (Mission 2)
    printf("The average score and s.d of Section %d ", student_section);
    printf("are %.2f and %.2f, respectively.\n", sec_mean, sqrt(sec_var));

    // get student's score
    int student_score;
    if (student_section == 1)
    {
        student_score = sec_scores[index1];
    }
    else
    {
        student_score = sec_scores[index2];
    }

    // sort scores
    sortArray(sec_scores, num_sec_students);

    // find student's rank in the section
    int student_rank = findRank(student_score, sec_scores, num_sec_students);

    // (Mission 3)
    printf("The student's score is %d and the rank is %d in Section %d.\n",
        student_score, student_rank, student_section);

    return 0;
}
