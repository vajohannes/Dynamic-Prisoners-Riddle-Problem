#include <iostream>
#include <ctime>
using namespace std;

/* -------------------------------------------------------------- */
/* This part serves as a pseudo random number generator for auto grade purpose only */
/* You are suggested not to refer to these codes in this assignment. */
/* You are not allowed to use global variables in this course. */
unsigned int next_num = 1; // Here we initiate an unsigned integer to be used in the following functions.

unsigned int pa1_rand() // This function is used to return a pseudo random number from 0 to 32767.
{
    next_num = next_num * 1103515245 + 2011;
    return static_cast<unsigned int>(next_num / 65536) % 32768;
}
void pa1_srand(unsigned int seed) // This function is used to set a seed of the pseudo random number generator.
{
    next_num = seed;
}
/* Everytime you call pa1_rand(), you will get a new pseudo random number. For the same seed, the sequence of pseudo
   random number is fixed. For example, when seed = 3, the sequence of pseudo random number is fixed to be [17746,
   30897, 9622, 18921, 4034, 17510, 24152, 14388, 23665, 31532, ...]. When seed = 5, the sequence of pseudo random
   number is fixed to be [18655, 32247, 9873, 9718, 26373, 27678, 5314, 22512, 31845, 22885, ...] */
/* -------------------------------------------------------------- */

const int MAX_BOXES = 1000; // This constant stores the largest length of boxes[]. You can use it in your code.

// This function is used to fill the 1D array with a random sequence of unique numbers from 1 to the user input for the number of prisoners
void placeSlips(int boxes[], int num_prisoners)
{
    for (int i = 0; i < num_prisoners; i++)
        boxes[i] = -1;
    int counter = 0;
    while (counter < num_prisoners)
    {
        int num = pa1_rand() % (num_prisoners);
        if (boxes[num] == -1)
        {
            boxes[num] = counter;
            counter++;
        }
    }
}

// TASK 1: Simulate an actual riddle room
bool simulateRoom(const int boxes[], int num_prisoners, int num_trials)
{
    bool bendera[num_prisoners]; // As a flag to check whether certain conditions are met
    for (int i = 0; i < num_prisoners; i++)
    {
        bendera[i] = false;
    }
    bool prisonerFail = false;
    for (int j = 0; j < num_prisoners; j++)
    {
        prisonerFail = false;
        int checkNum = j;
        if (!bendera[checkNum])
        {
            bendera[checkNum] = true;
            for (int k = 0; k < num_trials; k++)
            {
                if (boxes[checkNum] == j)
                {
                    break;
                }
                else if (k == num_trials - 1)
                {
                    prisonerFail = true;
                    break;
                }
                else
                {
                    bendera[boxes[checkNum]] = true;
                    checkNum = boxes[checkNum];
                }
            }
            if (prisonerFail)
                break;
        }
    }
    if (prisonerFail)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// TASK 2: Display certain statistics for a given room
void statsRoom(const int boxes[], int num_prisoners, int num_trials)
{

    bool array[num_prisoners];
    int storage[num_prisoners];
    int largest_loop[num_prisoners];
    int longest_loop_length = 0;
    int smallest_loop_length = num_prisoners;
    int found_slips = 0;
    int num_loops = 0;
    for (int i = 0; i < num_prisoners; i++)
    {
        array[i] = false;
    }
    bool prisonerFail = false;
    for (int j = 0; j < num_prisoners; j++)
    {
        prisonerFail = false;
        int checkNum = j;
        int z = 0;
        if (!array[checkNum])
        {
            array[checkNum] = true;
            for (int k = 0;; k++)
            {
                if (boxes[checkNum] == j)
                {
                    storage[z] = checkNum;
                    z++;
                    break;
                }
                else
                {
                    array[boxes[checkNum]] = true;
                    storage[z] = checkNum;
                    z++;
                    checkNum = boxes[checkNum];
                }
            }
        }

        if (z > 0)
        {
            num_loops++;
        }
        if (z <= num_trials)
        {
            found_slips += z;
        }
        if (z < smallest_loop_length && z > 0)
        {
            smallest_loop_length = z;
        }
        if (longest_loop_length < z)
        {
            longest_loop_length = z;
            for (int i = 0; i < longest_loop_length; i++)
            {
                largest_loop[i] = storage[i];
            }
        }
    }

    cout << "The number of prisoners who find their slips: " << found_slips << endl;
    cout << "Number of loops: " << num_loops << endl;
    cout << "Smallest loop length: " << smallest_loop_length << endl;
    cout << "Longest loop length: " << longest_loop_length << endl;
    cout << "Largest loop: ";
    for (int i = 0; i < longest_loop_length; i++)
    {
        cout << largest_loop[i] << " ";
    }

    cout << endl;
}

// TASK 3: Find the number of instances in 1000 rooms when the prisoners will all be able to escape
double successRooms(int boxes[], int num_prisoners, int num_trials) //  suceess rate of 1000 rooms basically repeating it a 1000 times
{

    int numberOfSuccess = 0;
    for (int i = 0; i < 1000; i++)
    {
        placeSlips(boxes, num_prisoners);
        if (simulateRoom(boxes, num_prisoners, num_trials) == true)
        {
            numberOfSuccess += 1;
        }
    }
    return numberOfSuccess;
}

// TASK 4: Nice guard will help the prisoners to successfully leave the room by breaking any loop which is greater than the number of trials
//         Return true if the intervention was applied, else return false
bool niceGuard(int boxes[], int num_prisoners, int num_trials)
{

    bool array[num_prisoners];
    int storage[num_prisoners];
    int largest_loop[num_prisoners];
    int longest_loop_length = 0;
    int smallest_loop_length = num_prisoners;
    int found_slips = 0;
    int num_loops = 0;
    int breakLoop, newLoop;
    for (int i = 0; i < num_prisoners; i++)
    {
        array[i] = false;
    }
    bool prisonerFail = false;
    for (int j = 0; j < num_prisoners; j++)
    {
        prisonerFail = false;
        int checkNum = j;
        int z = 0;
        if (!array[checkNum])
        {
            array[checkNum] = true;
            for (int k = 0;; k++)
            {
                if (boxes[checkNum] == j)
                {
                    storage[z] = checkNum;
                    z++;
                    break;
                }
                else
                {
                    array[boxes[checkNum]] = true;
                    storage[z] = checkNum;
                    z++;
                    checkNum = boxes[checkNum];
                }
            }
        }

        if (longest_loop_length < z)
        {
            longest_loop_length = z;
            for (int i = 0; i < longest_loop_length; i++)
            {
                largest_loop[i] = storage[i];
            }
        }
    }
    if (longest_loop_length > num_trials)
    {
        breakLoop = longest_loop_length / 2;
        if (longest_loop_length % 2 == 0)
        {
            breakLoop--;
        }
        newLoop = longest_loop_length - 1;

        boxes[largest_loop[breakLoop]] = largest_loop[0];
        boxes[largest_loop[newLoop]] = largest_loop[breakLoop + 1];
        return true;
    }
    else
    {
        return false;
    }
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED.

int main()
{

    int num_prisoners, num_trials, seed;
    // set boxes, priosoners

    cout << "Enter the number of prisoners (from 1 to 1000) :" << endl;
    cin >> num_prisoners;
    cout << "Enter the number of boxes each prisoner can open (from 1 to 1000) :" << endl;
    cin >> num_trials;
    cout << "Enter the seed for randomization else enter 0 and the system will randomize for you :" << endl;
    cin >> seed;

    if (seed == 0)
    {
        pa1_srand(time(NULL));
    }
    else
    {
        pa1_srand(seed);
    }

    int boxes[MAX_BOXES]; // array for the boxes
    for (int i = 0; i < MAX_BOXES; i++)
        boxes[i] = 0;

    int choice;
    cout << "Please choose an option:" << endl;
    cout << "0.Print the boxes" << endl;
    cout << "1.Simulate a room" << endl;
    cout << "2.Compute statistics of a room:" << endl;
    cout << "3.Compute success rate over 1000 rooms" << endl;
    cout << "4.Apply nice guard intervention in a room" << endl;
    cin >> choice;

    switch (choice)
    {
    case 0:
        placeSlips(boxes, num_prisoners);
        for (int i = 0; i < num_prisoners; i++)
            cout << boxes[i] << " ";
        cout << endl;
        break;
    case 1:
        placeSlips(boxes, num_prisoners);
        if (simulateRoom(boxes, num_prisoners, num_trials) == true)
        {
            cout << "Success! All prisoners found their slip." << endl;
        }
        else
        {
            cout << "Failure! Not all prisoners were able to find their slip." << endl;
        }
        break;
    case 2:
        placeSlips(boxes, num_prisoners);
        statsRoom(boxes, num_prisoners, num_trials);
        break;
    case 3:
    {

        double prisoners_left = successRooms(boxes, num_prisoners, num_trials);
        cout << "All prisoners were able to leave " << prisoners_left << "/1000 of the rooms." << endl;
    }
    break;
    case 4:
    {
        placeSlips(boxes, num_prisoners);
        int copy_arr[MAX_BOXES];
        for (int i = 0; i < num_prisoners; i++)
        {
            copy_arr[i] = boxes[i]; // copying the array for checking if no more than 2 swaps are made
        }

        bool nice_guard_val = niceGuard(boxes, num_prisoners, num_trials);

        int swap_count = 0;
        for (int j = 0; j < num_prisoners; j++)
        {
            if (copy_arr[j] != boxes[j])
            {
                swap_count++;
            }
        }
        if (swap_count > 2)
        {
            cout << "Illegal intervention as you have more than 1 swap " << endl;
        }
        else
        {
            if (nice_guard_val == false)
                cout << "No intervention needed." << endl;
            else
            {
                cout << "Intervention applied." << endl;
                // validity function
                bool prisoners_left = simulateRoom(boxes, num_prisoners, num_trials);
                // should return true
                if (prisoners_left == true)
                    cout << "All the prisoners were able to escape" << endl;
                else
                {
                    cout << "All the prisoners were not able to escape" << endl;
                }
            }
        }
    }
    break;
    }

    return 0;
}
