#include <iostream>
#include "string.h"


using namespace std;


/**
 * This program represents a simplified version of the Duolingo application (program for 
 * learning foreign languages).
 * It gives to the user the ability to create a course for a specific language, backed with
 * a list (pool) of questions that are defined by a translator, and give tests for a module
 * to the user that are to be defined with increasing difficulty (this depend on the
 * translator himself). The user is not allowed to proceed further with the modules, in
 * case the previous module was not finished with satisfying results, which for the current
 * perposes is 80% right questions.
 */



const int QUESTIONS_COUNT_PER_MODULE  = 10;
const int QUESTION_TEXT_LENGHT        = 100;
const int QUESTIONS_POOL_NUMBER_MAX   = 100;
const int NEXT_MODULE_REQUIRED_SCORE  = 80; // percents
const int SKILLS_MAX_COUNT_PER_COURSE = 20;

// enum QuestionTypes {
//     BASIC, SENTANCE
// };

/// Reduces an array of bools to a single value, i.e. counts the number of positive items.
/// Note: this is well known, widely used function from the Functional programming
int reduce(const bool *arr, int arrSize, int acc) {
    for (int i = 0; i < arrSize; ++i) {
        acc += arr[i];
    }
    return acc;
}

// Represents a text question
class Question
{
    public:
        Question (const char* type, const char* text, const char* answer) {
            strcpy(m_text, text);
            strcpy(m_answer, answer);

            m_type = new char[strlen(type) + 1];
            strcpy(m_type, type);
        }

        // XXX there is a proper place for this method
        // Just a simple comparison...
        bool        checkAnswer(const char* answer) {
            return !strcmp(m_answer, answer);
        }

        const char* getText() const {
            return m_text;
        }

        const char* getAnswer() const {
            return m_answer;
        }

        const char* getType() const {
            return m_type;
        }

    private:
        char *m_type;

        // keep it as simple as possible
        char m_text[QUESTION_TEXT_LENGHT];
        char m_answer[QUESTION_TEXT_LENGHT];
};


/// Filters a list of items, resulting in a list of items matching the type criteria, i.e.
/// get only those items that are of the given type.
/// N.B.!: Items are not copied but referenced. This saves some memory, but is more or less
/// a side effect. When filtering items you expect to get a fresh copy of those items.
/// Note: this is well known, widely used function from the Functional programming
Question** filter(Question* items, int itemsCount, char* type, int& count) {
    int matchingItemsCount = 0;

    for (int i = 0; i < itemsCount; ++i) {
        if (!strcmp(items[i].getType(), type)) {
            matchingItemsCount++;
            // DEV
            cout << items[i].getType() << endl;
            cout << items[i].getText() << endl;
        }
    }

    count = matchingItemsCount;
    // We use array of pointers in order to use the same Question objects.
    // As we don't have default constructor for the Question class, creating
    // a normal empty array is not possible
    // N.B.! this array has to be destroyed from the outside
    Question** result = new Question*[matchingItemsCount];

    for (int i = 0; i < itemsCount && matchingItemsCount > 0; i++) {
        if (!strcmp(items[i].getType(), type)) {
            // reuse the existing counter in a bit strange way
            // set relation to the same object
            result[--matchingItemsCount] = &items[i];
        }
    }

    for (int i = 0; i < count; ++i) {
        cout << result[i]->getText() << endl;
    }

    return result;
}


class Skill
{
    public:
        // Note: takes a dynamic array of questions that should will be cleared
        // after with the object's destruction
        Skill (char* name, Question** questionsPool, int poolSize, char* type)
            : m_questionsCount(0), m_lastTakenQuestionIdx(0),
            m_questionPoolCount(poolSize), m_questionsPool(questionsPool) {
                m_name = new char[strlen(name) + 1];
                strcpy(m_name, name);

                m_questionsType = new char[strlen(type) + 1];
                strcpy(m_questionsType, type);
            }

        ~Skill() {
            delete [] m_name;
            delete [] m_questionsType;

            // Take care of the dynamic memory, although it wasn't allocated in this class
            delete [] m_questionsPool;
        }

        /// Generate a fresh set of questions and give them to the user to solve.
        void retakeSkill(); 

        /// Get the score for the module represented in percents.
        int getScore() const {
            // questions have same weight
            int size = reduce(m_results, m_questionsCount, 0);

            // Casting is needed in order for the division not to be rounded, e.g. 1 / 2 -> 0 and not 0.5
            return ((double)size / m_questionsCount) * 100; 
        }

        void printResult() const {
            // TODO
        }

        /// Simple getter for `name`
        const char* getName() const {
            return m_name;
        }

    private:
        /// A method 
        void regenerateQuestions(); 

    private:
        char*    m_name;

        // Just keep some idea of what kind of questions are here
        // it might be handy sometime in the future
        char     *m_questionsType;

        // latest set of questions; they are regenerated every time
        Question *m_questions[QUESTIONS_COUNT_PER_MODULE]; // latest set of questions
        int      m_questionsCount;                // questions might be less than the allowed number
        bool     m_results[QUESTIONS_COUNT_PER_MODULE];   // right or wrong questions from last taken

        int      m_lastTakenQuestionIdx; // questions are taken sequentially
        int      m_questionPoolCount;    // number of questions in the pool
        Question **m_questionsPool;
};


void Skill::regenerateQuestions() {
    /*
     * Different ideas for questions generation:
     * - take questions randomly
     * - take questions that have not been given before
     * - some other heuristics...
     */

    // we might have just a small pool of questions
    m_questionsCount = QUESTIONS_COUNT_PER_MODULE < m_questionPoolCount ? QUESTIONS_COUNT_PER_MODULE : m_questionPoolCount;
    // the simplest
    for (int i = 0; i < m_questionsCount; ++i) {
        m_questions[i] = m_questionsPool[m_lastTakenQuestionIdx];
        // and move the index, starting from the start if end is reached...
        m_lastTakenQuestionIdx = (m_lastTakenQuestionIdx + 1) % m_questionsCount;
    }
}


void Skill::retakeSkill() {
    regenerateQuestions(); // 10

    char answer[QUESTION_TEXT_LENGHT];

    for (int i = 0; i < m_questionsCount; ++i) {
        cout << "Translate into english: " << m_questions[i]->getText() << endl; // Translate into ...: ragazzo

        // prompt for answer
        cout << "> ";
        cin.getline(answer, QUESTION_TEXT_LENGHT);

        m_results[i] = m_questions[i]->checkAnswer(answer);

        if (!m_results[i]) {
            cout << "You are not trying hard enough. The right answer is: " << m_questions[i]->getAnswer() << endl;
        }
    }
}


/// Represents a whole course for a language. Each course has multiple skills
/// that are to be taken sequentially with increasing difficulty.
/// All questions have the same score (of 1) and in order for the user to proceed in
/// the skills she has to have a satisfying result on the previous skill.
class Course
{
    public:
        Course (const char* lang, Question* questionsPool, int poolSize)
            :m_lastSkillId(0), m_skillsCount(0) {
                strcpy(m_lang, lang);

                // copies all instances of the given questions
                m_questionsPool = questionsPool;
                m_poolSize = poolSize;
            }

        ~Course() {
            // Clean up all allocated objects (a bit obvious)
            for (int i = 0; i < m_skillsCount; ++i) {
                delete m_skills[i];
            }
        }

        void addSkill(char* name, char* questionType); 

        void listSkills() const; 

        void showProgress() const; 

        bool isSkillReachable(int id) const {
            return id == 0 || m_skills[id-1]->getScore() > NEXT_MODULE_REQUIRED_SCORE;
        }

        void takeSkillById(int id) {
            // The skill has already been taken
            if (isSkillReachable(id)) {
                m_skills[id]->retakeSkill();
            } else {
                cout << "Test has not been taken yet. You need to unlock it first" << endl;
            }
        }

        void takeNextSkill(); 

    private:
        char m_lang[6]; // bg, en, en_uk, en_us

        int m_lastSkillId;
        Skill* m_skills[SKILLS_MAX_COUNT_PER_COURSE];
        int m_skillsCount;

        // create Vector
        Question* m_questionsPool;
        int m_poolSize;
};


void Course::takeNextSkill() {
    if (m_lastSkillId >= m_skillsCount) {
        cout << "All modules done successfully!";
        return;
    }

    m_skills[m_lastSkillId]->retakeSkill();

    if (isSkillReachable(m_lastSkillId + 1))
        m_lastSkillId++;
}

void Course::showProgress() const {
    cout << "---  --- --- ---" << endl;
    cout << "--- Progress ---" << endl;
    cout << "---  --- --- ---" << endl;
    for (int i = 0; i < m_skillsCount; i++) {
        cout << m_skills[i]->getName() << ": " << m_skills[i]->getScore() << endl;
    }
}

void Course::listSkills() const {
    cout << "---  --- --- --- --" << endl;
    cout << "--- Skills list ---" << endl;
    cout << "---  --- --- --- --" << endl;
    for (int i = 0; i < m_skillsCount; i++) {
        cout << "Id: " << i << " Name: "<< m_skills[i]->getName() << endl;
    }
}

void Course::addSkill(char* name, char* questionType) {
    if (m_skillsCount >= SKILLS_MAX_COUNT_PER_COURSE) {
        // no place for skills left
        return;
    } 


    // keep the number of filtered questions
    int filteredQuestionsCount;

    // filter questions that match the given type
    Question **filteredQuestions = filter(m_questionsPool, m_poolSize, questionType, filteredQuestionsCount);
    m_skills[m_skillsCount++] = new Skill(name, filteredQuestions, filteredQuestionsCount, questionType);
}



int main()
{
    // char language[] = "en";


    Question q1("basic", "ragazzo", "boy");
    Question q2("basic", "ragazza", "girl");
    Question q3("basic 2", "ragazzi", "boys");

    Question q4("Food", "Sono un ragazzo", "I am a boy");

    Question questions[] = { q1, q2, q3, q4 };

    Course course("it", questions, 3);

    course.addSkill((char*)"Basics", (char*)"basic");

    course.listSkills();

    course.takeNextSkill();

    course.showProgress();

    return 0;
}


// code problems
// - find problems in code (idea problems, inconsistency, etc.)
// - comment over email

// what if:
// - we want different answer comparison alg (check method outside of question class)
// - we want different representation of the questions (why in skill class)
// - we want multiple types for a question - it may be applicable for different skills


/// todo
// - questiontype -> enum

/// todo extensible version of the program
// we could also just: shuffle(m_questionspool); take the first n
// 
// replace this dynamic array madness with string and vector

