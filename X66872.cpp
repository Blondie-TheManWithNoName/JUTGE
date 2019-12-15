 #include <vector>
 #include <cstddef>
 using namespace std;
 #include <iostream>
 typedef unsigned int nat;
 
 class Llista {
   // Llista simplement encadenada, sense fantasma i no circular.
   private:
     struct node {
       int info;  // Informació del node
       node *seg; // Punter al següent element
       node* ant;
     };
     node *_prim; // Punter al primer element
     nat _long;   // Nombre d’elements
 
   public:
     Llista();
     // Pre: True
     // Post: El p.i. és una llista buida.
 
     Llista(const vector<int> &v);
     // Pre: True
     // Post: El p.i. conté els elements de v amb el mateix ordre.
 
     ~Llista();
     // Post: Destrueix els elements del p.i.
 
     nat longitud() const;
     // Pre: True
     // Post: Retorna el nombre d’elements del p.i.
 
     void mostra() const;
     // Pre: True
     // Post: Mostra el p.i. pel canal estàndard de sortida.
 
     void separa(Llista &l2);
     // Pre: l2 és buida
     // Post: S’han separat els elements del p.i., quedant al p.i. els elements
     // de les posicions senars i a l2 els de les posicions parells.
     // Exemple: [2 5 3 8 1] => [2 3 1] i l2 = [5 8]
    
 // Aquí va la implementació del mètode separa
};

 void Llista::separa(Llista &l2) {
  nat size = _long;
  node *p1 = _prim;
  node* aux;
  for (nat i = 1; i < size; ++i) {
    node* ant = p1->seg;
    if (i%2 != 0) {
      if (l2._long == 0) {
        l2._prim = new node;
        l2._prim -> info = ant -> info;
        l2._prim -> seg = NULL;
        aux = l2._prim;
      }
      else {
          node* n = new node;
        n -> info = ant -> info;
        aux -> seg = n;
        aux = aux -> seg; 
        aux-> seg = NULL;
      }
      if (ant -> seg != NULL) {
        p1 -> seg = ant->seg;
        p1 = p1 -> seg;
      }
      else {
        p1 -> seg = NULL;
      }
      --_long;
      ++l2._long;
    }
  }
}



