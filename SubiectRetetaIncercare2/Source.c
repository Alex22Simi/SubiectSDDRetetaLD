#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Reteta
{
	unsigned int nrReteta;
	char* numePacient;
	char* numeMedic;
	char* statut;
	unsigned char nrMedicamente;
	float procentCompensare;
}Reteta;
typedef struct NodLd
{
	Reteta* info;
	struct NodLd* next;
	struct NodLd* prev;
}NodLd;
Reteta* initializareReteta(unsigned int nrReteta, const char* numePacient, const char* numeMedic, const char* statut, unsigned char nrMedicamente, float procentCompensare)
{
	Reteta* reteta = (Reteta*)malloc(sizeof(Reteta));
	reteta->nrReteta = nrReteta;
	reteta->numePacient = (char*)malloc(strlen(numePacient) + 1);
	strcpy(reteta->numePacient, numePacient);
	reteta->numeMedic = (char*)malloc(strlen(numeMedic) + 1);
	strcpy(reteta->numeMedic, numeMedic);
	reteta->statut = (char*)malloc(strlen(statut) + 1);
	strcpy(reteta->statut, statut);
	reteta->nrMedicamente = nrMedicamente;
	reteta->procentCompensare = procentCompensare;
	return reteta;
}
NodLd* initializareNodLd(Reteta* reteta)
{
	NodLd* nodNou = (NodLd*)malloc(sizeof(NodLd));
	nodNou->info = reteta;
	nodNou->next = NULL;
	nodNou->prev = NULL;
	return nodNou;
}
NodLd* inserareLaIndex(NodLd* cap, NodLd** coada, Reteta* reteta, int index) {
	NodLd* nodNou = initializareNodLd(reteta);

	if (index == 0) {
		nodNou->next = cap;
		if (cap != NULL) {
			cap->prev = nodNou;
		}
		cap = nodNou;
		if (*coada == NULL) {
			*coada = nodNou;
		}
	}
	else {
		NodLd* temp = cap;
		int indexCurent = 0;
		while (temp != NULL && indexCurent < index - 1) {
			temp = temp->next;
			indexCurent++;
		}

		if (temp == NULL) {
			if (*coada != NULL) {
				(*coada)->next = nodNou;
				nodNou->prev = *coada;
				*coada = nodNou;
			}
			else {
				cap = nodNou;
				*coada = nodNou;
			}
		}
		else {
			nodNou->next = temp->next;
			nodNou->prev = temp;
			if (temp->next != NULL) {
				temp->next->prev = nodNou;
			}
			temp->next = nodNou;
			if (nodNou->next == NULL) {
				*coada = nodNou;
			}
		}
	}

	return cap;
}
NodLd* inserareSfarsit(NodLd* cap, NodLd** coada, Reteta* reteta)
{
	NodLd* nodNou = initializareNodLd(reteta);
	if (cap == NULL)
	{
		cap = nodNou;
		*coada = nodNou;
	}
	else
	{
		(*coada)->next = nodNou;
		nodNou->prev = *coada;
		*coada = nodNou;
	}
	return cap;
}
NodLd* inserareInceput(NodLd* cap, NodLd** coada, Reteta* reteta)
{
	NodLd* nodNou = initializareNodLd(reteta);
	if (cap != NULL)
	{
		cap = nodNou;
		*coada = nodNou;
	}
	else
	{
		nodNou->next = cap;
		cap->prev = nodNou;
		cap = nodNou;
	}
	return cap;
}
void afisareLD(NodLd* cap)
{
	if (cap != NULL)
	{
		while (cap != NULL)
		{
			printf("%hu %s %s %s %hhu %f\n", cap->info->nrReteta, cap->info->numePacient, cap->info->numeMedic,
				cap->info->statut, cap->info->nrMedicamente, cap->info->procentCompensare);
			cap = cap->next;
		}
	}
}
void afisareInversaLD(NodLd* coada)
{
	if (coada != NULL)
	{
		while (coada != NULL)
		{
			printf("%hu %s %s %s %hhu %f\n", coada->info->nrReteta, coada->info->numePacient, coada->info->numeMedic,
				coada->info->statut, coada->info->nrMedicamente, coada->info->procentCompensare);
			coada = coada->prev;
		}
	}
}
void dezalocareLd(NodLd* cap)
{
	if (cap != NULL)
	{
		while (cap != NULL)
		{
			NodLd* temp = cap;
			cap = cap->next;
			free(temp->info->numePacient);
			free(temp->info->numeMedic);
			free(temp->info->statut);
			free(temp->info);
			free(temp);
		}
		printf("Dezalocarea a fost facuta cu succes!");
	}
}
//nr retete avand nr de medicamente peste un prag dat ca param
int nrRetete(NodLd* cap, int prag)
{
	int contor = 0;
	if (cap != NULL)
	{
		while (cap != NULL)
		{
			if (cap->info->nrMedicamente > prag)
			{

				contor++;
			}
			cap = cap->next;
		}
	}
	return contor;
}
//actualizare procent pt pacientul cu numele dat ca param
void actualizare(NodLd* cap, const char* numePacient)
{
	if (cap != NULL)
	{
		while (cap != NULL)
		{
			if (strcmp(cap->info->numePacient, numePacient) == 0)
			{
				cap->info->procentCompensare = cap->info->procentCompensare + 10;
			}
			cap = cap->next;
		}
	}
}
//stergere noduri pt nodurile cu nr de medicamente mai < decat un prag dat ca param
NodLd* stergereSubPrag(NodLd* cap, unsigned char prag, NodLd** coada)
{
	//parcurgere lista de la cap si elimin nodurile care au nr de medicamente sub prag
	while (cap != NULL && cap->info->nrMedicamente < prag)
	{
		NodLd* temp = cap;//se pastreaza referinta la nodul curenta pt a-l elibera mai tarziu
		cap = cap->next;//avansare
		if (cap != NULL)
		{
			cap->prev = NULL;//daca lista nu este goala, deconectam primul nod
		}
		else
		{
			*coada = NULL;//daca lista e goala, actualizam si coada
		}
		free(temp->info->numePacient);
		free(temp->info->numeMedic);
		free(temp->info->statut);
		free(temp->info);
		free(temp);
	}
	//parcurgere lista pt a gasi si a elimina nodurile din interiorul listei
	NodLd* temp = cap;
	while (temp != NULL && temp->next != NULL)
	{
		if (temp->next->info->nrMedicamente < prag)
		{
			NodLd* nodDeSters = temp->next;//pastram referinta la nodul care trb sters
			temp->next = temp->next->next;//sare peste nodul care trebuie sters
			if (temp->next != NULL)
			{
				temp->next->prev = temp;//actualizam legatura daca nu suntem la sfarsitul listei
			}
			else
			{
				*coada = temp; // Dacă ștergem ultimul nod, actualizăm coada
			}
			// Eliberăm memoria alocată pentru informațiile din nodul de șters
			free(nodDeSters->info->numePacient);
			free(nodDeSters->info->numeMedic);
			free(nodDeSters->info->statut);
			free(nodDeSters->info);
			free(nodDeSters); // Eliberăm memoria alocată pentru nod
		}
		else
		{
			temp = temp->next;//avansare nod daca nu trb sters
		}
	}
	return cap;
}

void main()
{
	FILE* f = fopen("Reteta.txt", "r");
	if (f != NULL)
	{
		char bufferLine[300], sep_list[] = ",\n";
		NodLd* cap = NULL;
		NodLd* coada = NULL;
		while (fgets(bufferLine, sizeof(bufferLine), f))
		{
			char* token = strtok(bufferLine, sep_list);
			unsigned int nrReteta = atoi(token);

			token = strtok(NULL, sep_list);
			char* numePacient = (char*)malloc(strlen(token) + 1);
			strcpy(numePacient, token);

			token = strtok(NULL, sep_list);
			char* numeMedic = (char*)malloc(strlen(token) + 1);
			strcpy(numeMedic, token);

			token = strtok(NULL, sep_list);
			char* statut = (char*)malloc(strlen(token) + 1);
			strcpy(statut, token);

			token = strtok(NULL, sep_list);
			unsigned char nrMedicamente = (unsigned char)atoi(token);

			token = strtok(NULL, sep_list);
			float procentCompensare = (float)atof(token);

			Reteta* reteta = initializareReteta(nrReteta, numePacient, numeMedic, statut, nrMedicamente, procentCompensare);
			cap = inserareSfarsit(cap, &coada, reteta);


		}
		fclose(f);
		afisareLD(cap);
		printf("--------------------------\n");
		afisareInversaLD(coada);

		printf("Cerinta2: \n");
		int nr = 0;
		nr = nrRetete(cap, 3);
		printf("%d\n", nr);

		printf("Cerinta3: \n");
		actualizare(cap, "Simionescu Alexandru");
		afisareLD(cap);
		printf("--------------------------\n");
		afisareInversaLD(coada);

		printf("Cerinta4: \n");
		cap = stergereSubPrag(cap, 5, &coada);
		afisareLD(cap);
		printf("--------------------------\n");
		afisareInversaLD(coada);

		printf("\n====================AFISARE LISTA DUPA INSERARE LA UN INDEX SPECIFICAT==========================\n");
		Reteta* nouaReteta = initializareReteta(12345, "Ion", "Ionescu", "Normal", 6, 75.0);
		cap = inserareLaIndex(cap, &coada, nouaReteta, 1);
		afisareLD(cap);

		dezalocareLd(cap);
	}
}