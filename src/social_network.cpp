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
    int number_of_communities;
    int number_of_members;
    int community_id;
    bool is_empty;
    User* first;
    Community* start;
    Community* following;

    Community(){
        this->number_of_communities = 0;
        this->number_of_members = 0;
        this->community_id = 0;
        this->is_empty = true;
        this->first = nullptr;
        this->start = nullptr;
        this->following = nullptr;

    }
    //inicialmente nuestra comunidad no tiene usuarios, está vacía, y no tiene comunidades siguientes

    void append_user(User* user){

        this->number_of_members++;

        if(first == nullptr){
            first = user;
            cout << "user added " << endl;
            return;
        } 
        // si la lista está vacía el primer usuario es el nodo cabecera de la lista


        User* last = first;
        while(last->next != nullptr){
            last = last->next;
        } 
        // moviéndonos a través de la lista

        last->next = user;
        cout << "user added " << endl;
        // enlistar el nuevo usuario al final de la lista
    }

    void print_list(Community* c){
        User* u = c->first;
        while(u != nullptr){
            cout << u->id << endl;
            u = u->next;
        }
    } // MODIFICAR PARA ESCRIBIR EN ARCHIVO

    void append_community(Community* community){
        
        this->number_of_communities++;

        if(start == nullptr){
            start = community;
            cout << "community added " << endl;
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
            cout << "Comunidad " << c->community_id + 1 << ":" << endl;
            print_list(c);
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

User* make_users_array(int number_users){
    User* users_array = new User[number_users];
    
    int i = 0;
    while(i < number_users){
        User u;
        users_array[i] = u;
        i++;
    }

    i = 0;
    while(i < number_users){
        users_array[i].id = i;
        i++;
    }

    return users_array;
}
//función que crea el arreglo de usuarios

void delete_matrix(bool** users_matrix, int m_users){
        int w = 0;
        while(w < m_users){
            delete[] users_matrix[w]; 
            w++;
        }
        delete[] users_matrix;
}
//Elimina la matriz dinámica

void make_connections(User* user, bool** users_matrix, User* users_array, int m_users, Community* community)
{
    int i = 0;

    while(i < m_users){
        if(users_matrix[user->id][i]){

            if(!(get_user_by_id(i, m_users, users_array)->visited && get_user_by_id(i, m_users, users_array)->is_in_community)){
                User* some_friend = get_user_by_id(i, m_users, users_array);
                
                some_friend->visited = true;
                some_friend->is_in_community = true;

                community->append_user(some_friend);

                make_connections(some_friend, users_matrix, users_array, m_users, community);
            }

        }

        i++;
    }
} 
//función de backtracking. Recorremos el arbol de amistades en DFS

void printing(int case_counter, Community* communities_list){
    int i = 0;
    while(i < case_counter){
        cout << "Caso " << i + 1 << ": " << endl;
        communities_list->print_communities();
        i++;
    }
}
// función para escribir en consola

void delete_communities(Community* communities_list){

        Community* c = communities_list->start;
        while(c != nullptr){
            Community* cmm = c->following;
            delete c;
            c = cmm;
        }
}

void get_data(){

    int c_cases = 0;
    int m_users = 0;
    int n_edges = 0;

    cin >> c_cases;
    int i = 0;
    while(i < c_cases){
        cin >> m_users;
        cin >> n_edges;
    
        bool** users_matrix = make_matrix(m_users); //matriz de usuarios x usuarios → sabemos quien tiene amistad con quien

        User* users_array = make_users_array(m_users); 
        //arreglo de usuarios → sirve para ir marcando

        Community* communities_list = new Community();
        //lista de comunidades

        int j = 0;
        while(j < n_edges){
            int p = 0;
            int q = 0;
            cin >> p;
            cin >> q;

            users_matrix[p][q] = true;
            users_matrix[q][p] = true;

            j++;
        }

        int community_counter = 0;

        int w = 0;
        while(w < m_users){

            if(!(users_array[w].is_in_community && users_array[w].visited))
            {
                users_array[w].is_in_community  = true;
                users_array[w].visited = true;
                User* present_user = &users_array[w];


                Community* com = new Community();
                
                com->community_id = community_counter;

                community_counter++;

                com->append_user(present_user);

                communities_list->append_community(com);
            
                make_connections(present_user, users_matrix, users_array, m_users, com);
            }

            w++;
        }
    
    
        printing(i + 1, communities_list);


        delete_matrix(users_matrix, m_users);
        delete[] users_array;
        delete_communities(communities_list);
        i++;
    }

}


int main(){

    get_data();

    return 0;
}