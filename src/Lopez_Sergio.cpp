#include <iostream>
#include <fstream>


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


    void append_community(Community* community){
        
        this->number_of_communities++;

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
    
    void print_list(Community* c, fstream &file_to_write){
        User* u = c->first;
        while(u != nullptr){
            file_to_write << u->id << endl;
            u = u->next;
        }
        file_to_write << endl;
    } // MODIFICAR PARA ESCRIBIR EN ARCHIVO

    void print_communities(fstream &file_to_write_on){

        Community* c = start;
        while(c != nullptr){
            sortLinkedList(c->first); // ordenamos la lista

            file_to_write_on << "Comunidad " << c->community_id + 1 << ":" << endl;
            print_list(c, file_to_write_on);
            c = c->following;
        } //MODIFICAR PARA ESCRIBIR EN ARCHIVO
    }

    void sortLinkedList(User* head) {
        bool swapped;
        User* ptr;
        User* last = nullptr;

        /* Bubble Sort */
        do {
            swapped = false;
            ptr = head;

            while (ptr->next != last) {
                if (ptr->id > ptr->next->id) {
    
                    int temp = ptr->id;
                    ptr->id = ptr->next->id;
                    ptr->next->id = temp;
                    swapped = true;
                } //estamos intercambiando id's no los elementos en sí

                ptr = ptr->next;
            }
            last = ptr;
        } while (swapped);
    } 
    // función que ordena la lista simplemente enlazada

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

void printing(Community* communities_list, int &this_case){

    fstream output_file;

    // Abre el archivo en modo lectura y escritura, y lo crea si no existe
    output_file.open("Sergio_Lopez.txt", ios::out | ios::app);

    if (!output_file) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }
    
    output_file << "Caso " << this_case + 1 << ": " << endl;
    communities_list->print_communities(output_file);

    this_case++;

    output_file.close();
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
// función para eliminar las comunidades

void read_output_file(){
    fstream file_to_read;

    file_to_read.open("Sergio_Lopez.txt", ios::in);

    if(!file_to_read){
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    string line;
    while (getline(file_to_read, line)) {
        cout << line << endl;
    }

    file_to_read.close();
}
// leer el archivo generado en consola

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
    
        int current_case_counter = i;

        printing(communities_list, current_case_counter);

        delete_matrix(users_matrix, m_users);
        delete[] users_array;
        delete_communities(communities_list);
        i++;
    }

    read_output_file();
}
// función para obtener datos, crear matriz booleana de usuarios x usuarios, arreglo de usuarios y comunidades 


int main(){

    get_data();

    return 0;
}