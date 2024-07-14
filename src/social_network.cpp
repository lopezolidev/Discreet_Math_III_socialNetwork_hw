#include <iostream>

using namespace std;

//clases
class User {
public:
    int id;
    User* next;
    bool visited;
    bool is_in_community;

    User(){
        this->id = 0;
        this->next = nullptr;
        this->visited = false;
        this->is_in_community = false;
    }

}; 
//clase de usuario. Objeto que representa a cada usuario en la red

class Community {
public:
    int number_of_members;
    int community_id;
    bool is_empty;
    User* first;
    Community* start;
    Community* following;

    Community(){
        this->number_of_members = 0;
        this->community_id = 0;
        this->is_empty = true;
        this->first = nullptr;
        this->start = nullptr;
        this->following = nullptr;

    }
    //inicialmente nuestra comunidad no tiene usuarios, está vacía, y no tiene comunidades siguientes

    void append_user(User* user){
        
        if(first == nullptr){
            first = user;
            return;
        } 
        // si la lista está vacía el primer usuario es el nodo cabecera de la lista


        User* last = first;
        while(last->next != nullptr){
            last = last->next;
        } 
        // moviéndonos a través de la lista

        last->next = user;
        // enlistar el nuevo usuario al final de la lista
    }

    void print_list(){
        User* u = first;
        while(u != nullptr){
            cout << u->id << endl;
            u = u->next;
        }
    } // MODIFICAR PARA ESCRIBIR EN ARCHIVO

    void append_community(Community* community){
        if(start == nullptr){
            start = community;
            return;
        }
        // si la lista de comunidades está vacía la primera apuntará a la nueva comunidad que estemos incluyendo

        Community* cmm = start;
        while(cmm->following != nullptr){
            cmm = cmm->following;
        }

        cmm->following = community;

        //agregando una nueva comunidad si la lista de comunidades no está vacía
    }

    void print_communities(){
        Community* c = start;
        while(c != nullptr){
            cout << "Comunidad " << c->community_id << ":" << endl;
            c = c->following;
        } //MODIFICAR PARA ESCRIBIR EN ARCHIVO
    }
};
// clase de comunidad y lista de comunidades a su vez. 

User* get_user_by_id(int target_id, int arr_size, User* users_array){

    int i = 0;
    while( i < arr_size ){
        if( users_array[i].id == target_id ){
            return &users_array[i];
        }

        i++;
    }

    return nullptr;
}
//función para buscar un usuario basado en su id

void make_matrix(){
    // le mandamos una matriz
    // llena todas las celdas con false
}


void get_data(){
    //recibimos datos de consola
    // al llegar a los usuarios creamos una matriz usuarios x usuarios y un arreglo de usuarios donde se inicializan todos
    // llenamos las celdas de la matriz con false
    //  guardamos las amistades en una matriz de 2 x amistades
    // leemos cada doble celda de la matriz de amistades y con esos valores marcamos true en la intersección de las celdas de la matriz de usuarios x usuarios
    

    //mandamos la lista de usuarios y la matriz a una función

    int c_cases = 0;
    int m_users = 0;
    int n_edges = 0;

    cin >> c_cases;
    int i = 0;
    while(i < c_cases){
        cin >> m_users;
        cin >> n_edges;
    

        i++;
    }

}

void make_connections(){
    // aquí se crean las comunidades y las amistades
    // se lee el arreglo de usuarios, se crea una comunidad con dicho usuario
    // se manda el arreglo y la matriz a una función recursiva que irá hilando las comunidades hasta que ya no hayan miembros de esa comunidad por marcar
    // se recorre la matriz y por cada TRUE se vuelve a llamar a la función 
}




int main(){

    get_data();

    return 0;
}