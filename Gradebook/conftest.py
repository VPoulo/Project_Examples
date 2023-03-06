import course_work as cw
import pytest

@pytest.fixture
def course_work_instance():
    object = cw.course_work
    return object

@pytest.fixture
def exam():
    object = cw.exam
    return object

@pytest.fixture
def assignment():
    object = cw.program_assignment
    return object

@pytest.fixture
def demo():
    object = cw.proficiency_demo
    return object
