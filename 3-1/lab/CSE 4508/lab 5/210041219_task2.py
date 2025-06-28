import os
from sqlalchemy import create_engine , Column , Integer , String , ForeignKey , Float
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker , relationship


current_directory = os.path.dirname(os.path.abspath(__file__))
database_path = os.path.join( current_directory , 'example.db')
engine = create_engine(f'sqlite:///{ database_path }')

Base = declarative_base()




#2.1 and 2.2
class Book(Base):
    __tablename__ = 'books'
    id = Column(Integer, primary_key=True)
    title = Column(String)
    author = Column(String)
    pub_year = Column(Integer)
    price = Column(Float)

Base.metadata.create_all(engine)

#2.3
Session = sessionmaker(bind=engine)
session = Session()


new_book = Book(title='The Great Gatsby', author='F. Scott Fitzgerald', pub_year=1925, price=10.99)
session.add(new_book)
session.commit()


#2.4
all_books = session.query(Book).all()
for book in all_books:
    print( book.title, book.author, book.pub_year, book.price )


#2.5
update_book = session.query(Book).filter_by(title='The Great Gatsby').first()
update_book.price = 12.99
session.commit()


#verify
print('After updating')
all_books = session.query(Book).all()
for book in all_books:
    print( book.title, book.author, book.pub_year, book.price )


#2.6
delete_book = session.query(Book).filter_by(title='The Great Gatsby').first()
session.delete(delete_book)
session.commit()


#verify
print('After deleting')
all_books = session.query(Book).all() 
for book in all_books:
    print( book.title, book.author, book.pub_year, book.price )

