#Vaughn Poulo
#CS202
#Program 4
#May 27, 2022
#COMMENTS HERE

from asyncio.windows_events import NULL
import course_work

class student:
    def __init__(self, aName):
        self.student_name = aName
        self.final_grade = None
        self.exam_count = 0;
        self.assignment_count = 0;
        self.demo_count = 0;
        self.head = NULL;



    #Calculates the final grade of the student.
    def calculate_final_grade(self):
        pass
    
    
    
    #Checks if the student is missing any assignments.
    def check_missing_assignments(self):
        pass
    
    
    
    #Add Course work to the list.
    def add_course_work(self):
        pass
    
    
        
class node:
    def __init__(self):
        grade_ptr = NULL
        next = NULL
        