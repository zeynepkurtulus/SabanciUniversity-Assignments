#include <iostream>
#include <string>
using namespace std;
int main()
{
    string room_name;
    int capacity;
    double allowed_capacity;
    double capacity_coefficient;
    int registered_students;
    int zoom_students;
    
    cout << "Welcome to CS201 physical classroom capacity checker." << endl;
    
    cout << "Please enter the room name: ";
    cin >> room_name;
    
    cout << "Please enter the room capacity: ";
    cin >> capacity;
    if (capacity < 0) {
        
        cout << "You have entered an invalid value for room capacity." << endl;
        
    }
    else {
        
        cout <<"Please enter the allowed capacity coefficient: ";
        cin >> capacity_coefficient;
        if ( capacity_coefficient > 0  && capacity_coefficient > 1) {
            
            cout << "You have entered an invalid value for capacity coefficient." << endl;
        }
        
        else {
            
            allowed_capacity = (capacity * capacity_coefficient);
            cout << "Please enter how many students are registered to your course: ";
            cin >> registered_students;
            
            if (registered_students < 0){
                cout << "You have entered an invalid value for registered students." << endl;
                
            }
            
            else {
                if (allowed_capacity >= registered_students){
                    
                    cout << room_name << " can allow all students to attend physical lectures." << endl;
                }
                
                else {
                    zoom_students = (registered_students - allowed_capacity);
                    cout << room_name << " cannot allow all students to attend physical lectures." << endl;
                    cout << "For each lecture " << zoom_students << " students must be selected to watch on Zoom." << endl;
                    
                    
                }
            }
            
            
            
            
        }
        
    }
    
    
        
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
