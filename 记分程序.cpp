#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
const string FILENAME="rank.txt";
struct User{
    int score;
    string name;
};
void help(){
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"-----------------------                    -----------------------"<<endl;
    cout<<"----------------------- Available Commands -----------------------"<<endl;
    cout<<"-----------------------                    -----------------------"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"--/enter [name] [score] - Add a new user with initial score     --"<<endl;
    cout<<"--/add [name] [score]   - Add score to an existing user         --"<<endl;
    cout<<"--/remove [name]        - Remove a user                         --"<<endl;
    cout<<"--/to [name] [score]    - Set a user's score to a specific value--"<<endl;
    cout<<"--/help                 - Display this help message             --"<<endl;
    cout<<"--/exit                 - Exit the program                      --"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<endl;
}
vector<User> load(){
    vector<User> users;
    ifstream infile(FILENAME);
    string name;
    int score;
    while(infile>>name>>score){
        users.push_back({score,name});
    }
    infile.close();
    return users;
}
bool cmp(User &a,User &b){
	return a.score>b.score;
}
void saveUsers(vector<User> &users){
    sort(users.begin(),users.end(),cmp);
    ofstream outfile(FILENAME);
    for(const auto &user:users){
        outfile<<user.name<<' '<<user.score<<endl;
    }
    outfile.close();
}
int find(vector<User> &users,const string &name) {
    for(int i=0;i<int(users.size());i++){
        if(users[i].name==name){
            return i;
        }
    }
    return -1;
}
int main(){
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"---------------------                        ---------------------"<<endl;
    cout<<"--------------------- Rank Management System ---------------------"<<endl;
    cout<<"---------------------                        ---------------------"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"--------------                                     ---------------"<<endl;
    cout<<"--------------Print /help to display a help message---------------"<<endl;
    cout<<"--------------                                     ---------------"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    while(1){
        vector<User> users=load();
        cout<<"> ";
        string line;
        if(!getline(cin,line)) break;
        if(line.empty()) continue;
        stringstream ss(line);
        string com;
        ss>>com;
        if(com=="/exit"){
            cout<<"Exiting program";
            for(int i=1;i<=6;i++){
            	Sleep(100);
            	cout<<'.';
			}
			cout<<endl;
            break;
        }
        if(com=="/help"){
            help();
            continue;
        }
        string name;
        int x=0;
        bool dat=false;
        if(!(ss>>name)){
            cout<<"[Error] Missing name argument."<<endl;
            continue;
        }
        if(com=="/enter"){
            if(ss>>x){
                int idx=find(users,name);
                if(idx==-1){
                    users.push_back({x,name});
                    dat=1;
                    cout<<"[System] User "<<name<<" added with score "<<x<<"."<<endl;
                }else{
                    cout<<"[Error] User "<<name<<" already exists."<<endl;
                }
            }else{
                cout<<"[Error] Missing score argument. Usage: /enter [name] [score]" << endl;
            }
        } 
        else if(com=="/add"){
            if(ss>>x){
                int idx=find(users,name);
                if(idx!=-1){
                    users[idx].score+=x;
                    dat=1;
                    cout<<"[System] Added "<<x<<" to "<<name<<". New score: "<<users[idx].score<<"."<<endl;
                }else{
                    cout<<"[Error] User "<<name<<" not found."<<endl;
                }
            }else{
                cout<<"[Error] Missing score argument. Usage: /add [name] [score]"<<endl;
            }
        } 
        else if(com=="/remove"){
            int idx=find(users,name);
            if(idx!=-1){
                users.erase(users.begin()+idx);
                dat=1;
                cout<<"[System] User "<<name<<" removed."<<endl;
            }else{
                cout<<"[Error] User "<<name<<" not found."<<endl;
            }
        } 
        else if(com=="/to"){
            if(ss>>x){
                int idx=find(users,name);
                if(idx!=-1){
                    users[idx].score=x;
                    dat=1;
                    cout<<"[System] "<<name<<"'s score set to "<<x<<"."<<endl;
                }else{
                    cout<<"[Error] User "<<name<<" not found."<<endl;
                }
            }else{
                cout<<"[Error] Missing score argument. Usage: /to [name] [score]"<<endl;
            }
        } 
        else{
            cout<<"[Error] Unknown command: "<<com<<". Type /help for usage."<<endl;
        }
        if(dat){
            saveUsers(users);
        }
    }
}
