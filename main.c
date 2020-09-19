#include <stdio.h>
#include <stdlib.h>


void bot_cd_move(int *eval, int *guess)
{
	/*
	 *static int *prev_guess = {1, 1, 2, 2};
	 *static int *best_guess = {1, 1, 2, 2};
	 *static int *prev_eval = {0, 0, 0};
	 *int *curr_eval = {0, 0, 0};
	 *static left = 0;
	 *int sum = 0, i = 0, temp = 0;
	*/
	int i = 0, temp = 0;

	/* Naive solution no values repeated */
	srand((unsigned) time(&t));
	for (temp = rand(), i = 0; i < 4; i++, temp++)
		guess[i] = (temp % 4) + 1;
	return;
	/*
	 *for (i = 0; i < 4; i++)
	 *{
	 *	sum += eval[i];
	 *	curr_eval[eval[i]]++;
	 *}
	 *if (sum == 0)
	 *{
	 *	guess = prev_guess;
	 *	return;
	 *}
	 *if (curr_eval[2] < prev_eval[2])
	 *{
	 *	for (i = 0; i < 4; i++)
	 *		guess[i] = prev_guess[i];
	 *	if (left)
	 *	{
	 *		temp = guess[2];
	 *		guess[2] = guess[3];
	 *		guess[3] = temp;
	 *		left = 0;
	 *	}
	 *	else
	 *	{
	 *		temp = guess[0];
	 *		guess[0] = guess[1];
	 *		guess[1] = temp;
	 *		left = 1;
	 *	}
	 *}
	*/
}

void do_eval(int *eval, int *clrs_eval, int *guess)
{
	for (i = 0; i < 4; i++)
	{
		/* loop to go through guess */
		if (eval[i] != 2)
		{
			if (clrs_eval[guess[i]] != 0)
			{
				eval[i] = 1;
				clrs_eval[guess[i]]--;
			}
		}
	}
}

/**
 * play_1_1 -
 *
 * @first_role:
 * @sec_role:
 * Descriptions:
 *   For secret and guess code: Colors from 1 to 4, 0 means no color placed
 *   For eval: 0 for wrong color/place, 1 for correct color only,
 *             2 for correct color/place.
 */


void play_1_1(int first_role, int sec_role)
{
	int secret[] = {0, 0, 0, 0}, eval[] = {0, 0, 0, 0};
	int clrs_used[] = {0, 0, 0, 0}, clrs_eval[] = {0, 0, 0, 0};
	int guess[] = {0, 0, 0, 0};
	int did_it = 0, round = 1;
	int i = 0, j = 0;

	printf("Mastermind! make your secret code\n");
	/* Enable only mastermind to input the secret code*/
	for (i = 0; i < 4; i++)
	{
		secret[i] = i + 1;
		clrs_used[secret[i]]++;
	}

	for (round = 1; round <= 9; round++)
	{
		for (i = 0; i < 4; i++)
			clrs_eval[i] = clrs_used[i];
		printf("Codebreaker!! time to break the code\n");
		printf("Try your best guess and place your marbles");
		printf("in the slots of the round %d\n", round);

		/* Awaits for user to place the marbles and return the array*/
		guess = cb_move();
		did_it = 1;
		for (i = 0; i < 4; i++)
		{
			if (guess[i] != secret[i])
			{
				did_it = 0;
				eval[i] = 0;
				continue;
			}
			eval[i] = 2;
			clrs_eval[guess[i]]--;
		}
		if (did_it)
		{
			printf("Congratulations!! You braked the code\n");
			printf("Mastermind... make it harder next time\n");
			return;
		}
		do_eval(eval, clrs_eval, guess);
		/* We can either let the MM to place the evaluation*/
		printf("Mastermind! evaluate the codebreaker's move\n");
		/* Or we could place the evaluation */
		place_eval_on_board(eval);
	}
	printf("Aawww what a bummer!! Codebreaker couldn't do it!\n");
	printf("Mastermind, that was though!! Congratulations!!\n");
	return;
}


void play_1_bot(int first)
{
	int secret[] = {0, 0, 0, 0}, eval[] = {0, 0, 0, 0};
	int clrs_used[] = {0, 0, 0, 0}, clrs_eval[] = {0, 0, 0, 0};
	int guess[] = {0, 0, 0, 0};
	int did_it = 0, round = 1;
	int i = 0, j = 0;
	time_t t;

	printf("Mastermind! make your secret code\n");
	/* Enable only mastermind to input the secret code*/
	if (first == 1)
	{
		/*Code where user creates the secret*/
		for (i = 0; i < 4; i++)
		{
			secret[i] = i + 1;
			clrs_used[secret[i]]++;
		}
	}
	else
	{
		/* If bot is mastermind: gen random secret*/
		srand((unsigned) time(&t));
		for (i = 0; i < 4; i++)
		{
			secret[i] = (rand() % 4) + 1;
			clrs_used[secret[i]]++;
		}
	}

	for (round = 1; round <= 9; round++)
	{
		/*Restoring the colors count for a later eval*/
		for (i = 0; i < 4; i++)
			clrs_eval[i] = clrs_used[i];

		printf("Codebreaker!! time to break the code\n");
		printf("Try your best guess and place your marbles");
		printf("in the slots of the round %d\n", round);

		/* Awaits for Cb to place the marbles and return the array*/
		if (first_role == 2)
			guess = cb_move();
		else
			bot_cd_move(eval, guess);

		did_it = 1;
		for (i = 0; i < 4; i++)
		{
			if (guess[i] != secret[i])
			{
				did_it = 0;
				eval[i] = 0;
				continue;
			}
			eval[i] = 2;
			clrs_eval[guess[i]]--;
		}
		if (did_it)
		{
			printf("Congratulations!! You braked the code\n");
			printf("Mastermind... make it harder next time\n");
			return;
		}
		for (i = 0; i < 4; i++)
		{
			/* loop to go through guess */
			if (eval[i] != 2)
			{
				if (clrs_eval[guess[i]] != 0)
				{
					eval[i] = 1;
					clrs_eval[guess[i]]--;
				}
			}
		}
		/* We can either let the MM to place the evaluation*/
		printf("Mastermind! evaluate the codebreaker's move\n");
		/* Or we could place the evaluation */
		place_eval_on_board(eval);
	}
	printf("Aawww what a bummer!! Codebreaker couldn't do it!\n");
	printf("Mastermind, that was though!! Congratulations!!\n");
	return;
}


/**
 *
 */


int main()
{
	int input = 0;
	int first_role = 0, sec_role = 0, bot = 0;
	int settings[] = {0, 0, 0};

	printf("Welcome to Mastermind!!\n");
	printf("More thrilling messages here buajajajaaa...\n");


	printf("Please select game mode:\n");
	printf("1. 1 vs 1\n");
	printf("2. 1 vs Bot\n");
	printf("3. How to play Mastermind\n");
	printf("4. Exit\n");

	/* Let's say it was a...*/
	input = 1;

	switch (input)
	{
	case 1:
		/* 1 vs 1 */
		bot = 0;
		printf("Choose P1 role:\n");
		printf("1. Mastermind\n");
		printf("2. Codebreaker\n");
		/* let's say player choose 1 as mastermind*/
		first_role = 1;
		sec_role = 3 - first_role;
		settings[0] = first_role;
		settings[1] = sec_role;
		settings[2] = bot;
		play(settings, 3);
		break;
	case 2:
		/* 1 vs Bot */
		bot = 1;
		printf("Choose your role:\n");
		printf("1. Mastermind\n");
		printf("2. Codebreaker\n");
		/* let's say player choose 1 as mastermind*/
		first_role = 1;
		sec_role = 3 - first_role;
		settings[0] = first_role;
		settings[1] = sec_role;
		settings[2] = bot;
		play_1_vs_bot(settings);
		break;
	case 3:
		/* How to play Mastermind (Manual) */
		printf("Google it :)\n");
		break;
	case 4:
		/* Exit */
		break;
	default:
		printf("Unknown entry\n");
	}


	return (EXIT_SUCCESS);
}
