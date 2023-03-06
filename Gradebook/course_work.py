#Vaughn Poulo
#CS202
#Program 4
#May 27, 2022
#COMMENTS HERE

##I am debating using dynamic binding.


import numpy as np

##BASE CLASS COURSE WORK

class course_work:
    def __init__(self):
        self.course_name = "CS202";         #Name of the course course work is for.
        self.course_work_name = None;       #Name of the assignment (Ex. Midterm #1)
        self.course_work_type = None;       #Type of course work (Ex. Exam)
        self.grade = None;                  #Alphabetical representation of grade (A-F or P/NP)
        self.topics = None;                 #Topics covered in course work.
        self.weighted_grade = None;         #Weighted contribution to overall grade.
    
    
        
    #Prompts the user to enter information regarding the course work.    
    def get_info(self):
        pass
     
     
               
    #Display course work related information.
    def display(self):
        pass
    
    
    
    #Allows user to change course number if grade.
    def edit_course_number(self):
        pass
    
    
    
    #Allows user to add topics to the course work.
    def add_topic(self):
        pass
    
    
    
 
####CLASS EXAM
  
class exam(course_work):
    def __init__(self):
        course_work.__init__(self) #initialize base class.
        course_work.course_work_type = "Exam"
        self.weight = 0.20
        self.points_possible = 40
        self.points_earned = 0

       
        
    #Prompts user for information regarding exams
    def get_info(self):
        pass
    
    
    
    #Assigns letter grade to exam.
    def assign_letter_grade(self):
        pass
    
    
    
    #Assigns weighted grade to final grade.
    def assign_weighted_grade(self):
        pass
    
    
##CLASS PROGRAMMING ASSIGNMENT
  
class program_assignment(course_work):
    def __init__(self):
        course_work.__init__(self) #initialize base class.
        course_work.course_work_type = "Programming Assignment"
        self.weight = 0.05
        self.points_possible = 125
        self.points_earned = 0
        self.deliverables_list = np.array()   #Will hold scores and names of deliverables. MAYBE MAKE A DICTIONARY??
        

    
        
    #Prompts user for information regarding exams
    def get_info(self):
        pass
    
    
    
    #Assigns letter grade to exam.
    def assign_letter_grade(self):
        pass
    
    
    
    #Assigns weighted grade to final grade.
    def assign_weighted_grade(self):
        pass
    
    
    
##CLASS PROFICIENCY DEMO
  
class proficiency_demo(course_work):
    def __init__(self):
        course_work.__init__(self) #initialize base class.
        course_work.course_work_type = "Proficiency Demo"
        self.score_earned = None

       
        
    #Prompts user for information regarding exams
    def get_info(self):
        pass
    
    
    
    #Assigns letter grade to exam.
    def assign_letter_grade(self):
        pass
    
    
    
    #Assigns weighted grade to final grade.
    def assign_weighted_grade(self):
        pass