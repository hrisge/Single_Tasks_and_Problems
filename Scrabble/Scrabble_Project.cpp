#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

const constexpr size_t INITIAL_SIZE = 4096;
const constexpr size_t WORD_BUFF = 128;
const constexpr size_t alphabetSize = 'z' - 'a';
const char FILE_NAME[] = "dictionary.txt";

unsigned myStrlen(const char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;
	while (*str)
	{
		result++;
		str++;
	}
	return result;
}
void myStrcpy(const char* source, char* dest)
{
	if (!source || !dest)
		return;
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}
int myStrcmp(const char* first, const char* second)
{
	if (!first || !second)
		return 0;

	while ((*first) && (*second) && ((*first) == (*second)))
	{
		first++;
		second++;
	}

	return (*first - *second);

}
void myStrcat(char* first, const char* second)
{
	if (!first || !second)
		return;

	size_t firstLen = myStrlen(first);
	first += firstLen;
	myStrcpy(second, first);
}

void makeNull(char** dictionary, size_t size)
{
	for (int i = 0; i < size; i++)
		dictionary[i] = nullptr;
}
void resize(char**& dictionary, size_t oldSize, size_t newSize)
{
	if (newSize <= oldSize)
		return;

	char** newDictionary = new char* [newSize];
	for (int i = 0; i < oldSize; i++)
		newDictionary[i] = dictionary[i];

	makeNull(dictionary + oldSize, newSize - oldSize);

	delete[] dictionary;
	dictionary = newDictionary;
}

int loadWords(char** dictionary, size_t size)
{
	std::ifstream file(FILE_NAME);

	if (!file.is_open())
		return 0;

	int counter = 0;
	while (!file.eof())
	{
		if (counter > size)
		{
			resize(dictionary, size, size * 2);
			size *= 2;
		}

		dictionary[counter] = new char[WORD_BUFF];
		file.getline(dictionary[counter], WORD_BUFF, '\n');
		counter++;
	}

	resize(dictionary, size, size * 2);
	return (size * 2);
}

bool isWordInDictionary(char** dictionary, int dicLen, const char* word)
{
	size_t left = 0, right = dicLen - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		int res = myStrcmp(word, dictionary[mid]);
		if (res == 0)
			return 1;
		else if (res < 0)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return 0;
}
int findIndexToPutNewWord(char** dictionary, int len, const char* word)
{
	size_t left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		int res = myStrcmp(dictionary[mid], word) + myStrcmp(dictionary[mid-1], word);
		if (res == 0)
			return mid;
		else if (res < 0)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}

int chooseSetting()
{
	int setting;
	cout << "===== If you want to change the number of letters you receive enter 1 =====\n";
	cout << "===== If you want to change th number of Rounds enter 2 =================\n";
	cin >> setting;
	system("CLS");
	return setting;
}
void roundMessage(int round)
{
	cout << "===== Round " << round << " =====\n";
}
void printLetters(const char* letters)
{
	while (*letters)
	{
		cout << *letters << ' ';
		letters++;
	}
	cout << endl;
}
void printPoints(int points)
{
	cout << "===== Your point are " << points << " =====\n";
}
void inputWord(char* word, size_t len)
{
	cout << "Input Word: \n";
	cin.getline(word, len);
}
void goodbyeMessage()
{
	cout << "===== Thanks for Playing! Goodbye! =====\n";
	std::this_thread::sleep_for(std::chrono::seconds(5));
}
void invalidCommand()
{
	cout << "===== Invalid command! =====\n";
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

bool isWordValid(const char* word, const char* letters, size_t lettersCount)
{
	char* lettersCopy = new char[lettersCount];
	myStrcpy(letters, lettersCopy);
	while (*word)
	{
		bool found = false;
		for (int i = 0; i < lettersCount; i++)
		{
			if (*word == lettersCopy[i])
			{
				lettersCopy[i] = '*';
				word++;
				found = true;
				break;
			}
			else
				found = false;
		}
		if (found == false)
		{
			delete[] lettersCopy;
			return false;
		}
		word++;
	}
	delete[] lettersCopy;
	return true;
}

void playGame(char** dictionary, size_t dicLen, int rounds, int lettersCount)
{
	char* letters = new char[lettersCount + 1];
	int points = 0;
	for (int i = 0; i < rounds; i++)
	{
		//Generate and Print Letters
		for (int i = 0; i < lettersCount; i++)
			letters[i] = 'a' + (rand() % alphabetSize);
		letters[lettersCount] = '\0';
		printLetters(letters);

		//Input word
		char* word = new char[lettersCount + 1];
		inputWord(word, lettersCount + 1);
		bool valid = isWordValid(word, letters, lettersCount);

		if (!valid)
		{
			delete[] word;
			continue;
		}

		points += myStrlen(word);
		printPoints(points);
	}
	system("CLS");
	printPoints(points);
	delete[] letters;
}
void changeNumberOfLetters(int& numberOfLetters)
{
	int n;
	cout << "===== Enter the amount of Letters you want to receive =====\n";
	cin >> n;
	system("CLS");
	if (n <= 0)
	{
		cout << "===== The Number of Letters must be a Positive number =====\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
		return;
	}

	numberOfLetters = n;
	cout << "===== The Number of Letters have been changed =====\n";
	std::this_thread::sleep_for(std::chrono::seconds(5));
}
void changeNumberOfRounds(int& numberOfRounds)
{
	int n;
	cout << "===== Enter the number of Rouunds you want the Game to have =====\n";
	cin >> n;
	system("CLS");
	if (n <= 0)
	{
		cout << "===== The Number of Rounds must be a Positive number =====\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
		return;
	}

	numberOfRounds = n;
	cout << "===== The Number of Rounds have been changed =====\n";
	std::this_thread::sleep_for(std::chrono::seconds(5));
}
void addWordToDictionary(char** dictionary, int& dicLen)
{
	cout << "===== Type the Word you want to add to the dictionary =====\n";
	char* word = new char[WORD_BUFF];
	cin.getline(word, WORD_BUFF);
	if (isWordInDictionary(dictionary, dicLen, word))
	{
		cout << "===== This Word is already in the dictionary. Goiing back to menu =====\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
		return;
	}
	
	int index = findIndexToPutNewWord(dictionary, dicLen, word);
	char buff[WORD_BUFF];
	myStrcpy(word, buff);
	
	for (int i = index; i <= dicLen; i++)
	{
		myStrcpy(buff, dictionary[i]);
		myStrcpy(dictionary[i + 1], buff);
	}
	cout << "===== Word added successfully =====\n";
	std::this_thread::sleep_for(std::chrono::seconds(5));
}
void settings(char** dictionary, int& dicLen, int& rounds, int& numberOfLettersGiven)
{
	int setting = chooseSetting();
	switch (setting)
	{
	case 1: changeNumberOfLetters(numberOfLettersGiven);
		break;
	case 2: changeNumberOfRounds(rounds);
		break;
	default:
		invalidCommand();
		break;
	}(setting);
}

void scrabble()
{
	//Creating and loading Dictioanry from File
	char** dictionary;
	dictionary = new char* [INITIAL_SIZE];
	makeNull(dictionary, INITIAL_SIZE);
	int newSize = loadWords(dictionary, INITIAL_SIZE);

	int numberOfRounds = 10;
	int numberOfLettersGiven = 10;

	while (true)
	{
		system("CLS");
		cout << "====== Welcome to the Scrabble Game =================\n";
		cout << "====== If you want to Start the Game enter 1 ========\n";
		cout << "====== If you want to Open the Setings enter 2 ======\n";
		cout << "====== If you want to Add a Word enter 3 ============\n";
		cout << "====== If you want to Exit the Game enter 4 =========\n";

		int command;
		cin >> command;
		system("CLS");
		switch (command)
		{
		case 1:
			playGame(dictionary, newSize, numberOfRounds, numberOfLettersGiven);
			break;
		case 2:
			settings(dictionary, newSize, numberOfRounds, numberOfLettersGiven);
			break;
		case 3: 
			addWordToDictionary(dictionary, newSize);
			break;
		case 4:
			goodbyeMessage();
			return;
		default:
			invalidCommand();
			break;
		}
	}
}

int main()
{
	scrabble();
}