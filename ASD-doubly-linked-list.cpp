// Implementa le funzioni sulle liste realizzate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento

// FILE DA MODIFICARE

#include "ASD-doubly-linked-list.h"


using namespace list;

struct list::node {  // descrivo qui, fuori dal namespace, come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
    Elem info;
    node *prev;
    node *next;
};

/*************************************************/
/* Implementazione delle operazioni di utilita'  */
/*************************************************/

void readFromStream(istream& str, List& l) {
    createEmpty(l);
    Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    // assumiamo che il segnale di fine input nel file sia  FINEINPUT
    while (e != FINEINPUT)  {     
        addRear(e, l);   // aggiunge l'elemento alla fine della lista
        str>>e;
        if (!str) throw runtime_error("Errore inserimento dati\n");
    }
}

/* legge il contenuto di una lista da file */
void readFromFile(string nome_file, List& l) {
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    readFromStream(ifs, l);
}


/* legge il contenuto di una lista da standard input */
void readFromStdin(List& l) {
   cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
   readFromStream((std::cin), l);
}

/* stampa la lista */
void print(const List& l) {
   List q = l->next;  // q "salta la sentinella" e va alla testa della lista
   while (q != l) {   // avanza finche' non finisce la lista
      cout << q->info << "; ";
      q = q->next; 
    }
}

/**************************************************/
/* Implementazione delle operazioni nel namespace */
/**************************************************/

/* crea la lista vuota */
void list::createEmpty(List& l) {
   
   list::node *sent=new list::node; //Creiamo la sentinella
   l=sent; //La nuova lista punta alla sentinella appena creata
   //Visto che è presente soltanto la sentinella, dovrà puntare sia percendemente che successivamente a se stessa
   sent->next=l;
   sent->prev=l;
   
}

/* "smantella" la lista svuotandola */
void list::clear(const List& l) {
	List p = l->next;
	List aux = p;
	while(aux != l)
	{	
		p = aux;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		p = NULL;
		aux=aux->next;
	}
}

/* restituisce l'elemento in posizione pos se presente; restituisce un elemento 
che per convenzione si decide che rappresenta l'elemento vuoto altrimenti*/
Elem list::get(int pos, const List& l) {
  int cont=0;
  List p=l->next;
  while(cont!=pos)
  {
  	if(p==l) 
  	{
		return -1000000; //Elemento vuoto
  	}
  	p=p->next;
  	cont++;
  }
  return p->info;
}

/* modifica l'elemento in posizione pos, se la posizione e' ammissibile */
void list::set(int pos, Elem e, const List& l) {
  int cont=0;
  List p=l->next;
  while(cont!=pos)
  {
  	if(p==l) 
  	{
  		cout<<"posizione sbagliata"<<endl;
  		return;
  	}
  	p=p->next;
  	cont++;
  }
  p->info=e;
}

/* inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
void list::add(int pos, Elem e, const List& l) {                                               
  int cont=0;
  List p=l->next;
  while(cont!=pos)
  {
  	if(p==l) 
  	{
  		cout<<"posizione sbagliata"<<endl;
  		return;
  	}
  	p=p->next;
  	cont++;
  }
  list::node *aux=new list::node;
  aux->info=e;
  aux->next=p;
  aux->prev=p->prev;
  p->prev=aux;
  aux->prev->next=aux;
  
}

/* inserisce l'elemento alla fine della lista */
void list::addRear(Elem e,  const List& l) {
		
    list::node *aux=new list::node;
    aux->info=e;
    if(l->next==l) l->next=aux;
    aux->prev=l->prev;
    aux->next=l;
    l->prev->next=aux;
    l->prev=aux;
}

/* inserisce l'elemento all'inizio della lista */
void list::addFront(Elem e, const List& l) {
     list::node *aux=new list::node;
     aux->info=e;
     l->next->prev=aux;
     aux->next=l->next;
     aux->prev=l;
     l->next=aux;
     
}

/* cancella l'elemento in posizione pos dalla lista */
void list::removePos(int pos, const List& l) {
	int cont=0;
  	List p=l->next;
  	while(cont!=pos)
  	{
  		if(p==l) 
  		{
  			cout<<"posizione sbagliata"<<endl;
  			return;
  		}
  		p=p->next;
  		cont++;
  	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	p = NULL;

}

 /* cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
void list::removeEl(Elem e, const List& l) {
	List p = l->next;
	List aux;
	while(p != l)
	{
  		if(p->info==e)
  		{
  			aux = p;
			aux->prev->next = aux->next;
			aux->next->prev = aux->prev;
			delete aux;
			aux = NULL;
  		}
  		p = p->next;
	}

}

/* restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
bool list::isEmpty(const List& l) {
  return l->next==l;
}

 /* restituisce la dimensione della lista */
int list::size(const List& l) {
   	List p = l->next;
   	int cont = 0;
	while(p != l)
	{
		cont++;
		p = p->next;
	}
	return cont;
}

