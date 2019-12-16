#include <iostream> 
using namespace std;

struct list {
	int value;
	list* next;
};


list* list_create(list* rt, int N) {

	list* el;

	//Erzeugung der Listenelemente 
	for (int ii = 0; ii < N; ii++) {
		el = new list;			//Erzeugung eines neuen Listenelements 
		el->value = ii;			//Wertzuweisung 
		el->next = rt;			//Element el an den Anfang der Liste setzen 
		rt = el;				//Listenanker setzen 
	}
	return rt;
}

void list_print(list* rt) {
	list* p;
	p = rt;							//Listenanfang holen 
	cout << "\t";
	while (p != NULL) {				//Schleife über alle Listenelemente 
		cout << p->value << ", ";	//Ausgabe des Wertes 
		p = p->next;				//Nächstes Listenelement holen 
	}
}

void list_delete(list* rt) {
	list* p;
	p = rt;								//Listenanfang holen 
	while (p != NULL) {					//Schleife über alle Listenelemente 
		rt = p;							//Element holen 
		p = p->next;					//Auf das nächste Element weiterschalten 
		delete rt;						//Element löschen 
	}
	rt = NULL;							//Leere Liste erzeugen 
}

void main(void)
{
	list * rt = NULL, * p;
	int N, g;

	cout << "How many datasets do you want to create?\n\n Amount of sets: ";
	cin >> N;
	cout << endl;

	//Erzeugen der Liste und deren Inhalt
	rt = list_create(rt, N);

	//Ausgabe der Listenelemente 	
	list_print(rt);		
	cout << endl;

	//Rückgabe der Listenelemente 
	cout << "Do you want to delete the data?" << endl;
	cin >> g;

	if (g) 
	{
		list_delete(rt);
	}
	else{}

}