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

bool** make_matrix(int m_users){
    //recibe el número de usuarios

    bool** users_matrix = new bool*[m_users];
    // creamos la matriz

    for (int i = 0; i < m_users; ++i) {
        users_matrix[i] = new bool[m_users];
    }

    for (int i = 0; i < m_users; i++)
    {
        for (int j = 0; j < m_users; j++)
        {
            users_matrix[i][j] = false;
        }
    }
    // llena todas las celdas con false
    
    return users_matrix;
}
//función que retorna la matriz de usuarios x usuarios


void delete_matrix(bool** users_matrix, int m_users){
        int w = 0;
        while(w < m_users){
            delete[] users_matrix[w]; 
            w++;
        }
        delete[] users_matrix;
}
//Elimina la matriz dinámica



void make_connections(){
    // aquí se crean las comunidades y las amistades
    // se lee el arreglo de usuarios, se crea una comunidad con dicho usuario
    // se manda el arreglo y la matriz a una función recursiva que irá hilando las comunidades hasta que ya no hayan miembros de esa comunidad por marcar
    // se recorre la matriz y por cada TRUE se vuelve a llamar a la función 
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
    
        bool** users_matrix = make_matrix(m_users);


        cout << "edges: "<< n_edges << endl;

        int friendships[n_edges][2];    
        //arreglo fijo del tamaño de la cantidad de arcos en el grafo

        // int number_edges = 0;
        // while(number_edges < n_edges){
        //     int p = 0;
        //     int q = 0;
        //     cin >> p;
        //     cin >> q;
        //     friendships[0][number_edges] = p;
        //     friendships[1][number_edges] = q;
            
        //     number_edges++;
        // }
    
        // int f = 0;
        // while(f < n_edges){
        //     cout << friendships[0][n_edges] << " " << friendships[1][n_edges];
        //     cout << endl;
        //     f++;
        // }

    
    
    
    
    
    
        // int f = 0;
        // while(f < m_users){
        //     int g = 0;
        //     while(g < m_users){
        //         if(!users_matrix[f][g]) cout << "No connection ";
        //         g++;
        //     }
        //     cout << endl;
        //     f++;
        // }


        delete_matrix(users_matrix, m_users);

        i++;
    }

}


int main(){

    get_data();

    return 0;
}