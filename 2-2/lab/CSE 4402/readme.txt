~to manually run java-
javac app.java
java app
~no multiple inheritence in java
~access parent class constructor - super(name, temp);
access parent class attributes - super.name;
~ float in java - 0.1f
double in java - 0.1
~ to access static: className.staticMember.
ie: if cup is a class, cup.cupCount can access static var
~to create abstract class: public abstract class Vehicle{}
			   abstract void go();
~interface: 1.doesn't have attributes
	    2. doesn't contain regular methods
	    3. only has abstract methods
	    4. skeleton of a class
we use "IMPLEMENTS" keyword while inheriting from this
also use "public" keyword before abstract methods
multiple interfaces are allowed!! in that case all abstract methods from both classes have to be overridden.
multiple interfaces can have same named method in parent classes. because A DEFINITION ISN'T PROVIDED FOR THEM ANYWAYS. ONLY A DECLARATION IS GIVEN. so the definition we provide in the child class is the one that will be executed.

JAVAFX
-launch is a static method, that we inherit from application class
