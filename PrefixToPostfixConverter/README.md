# Trie
Trie built for the Data Structures and Algorithms class' homework
My idea sprung out 8 hours before I had to send the homework in. The idea is to have "reading heads", which would move according to the read letter and in case of a match to a word in the dictionary, to stop and check whether there is a head that was activated before the current one that is still working. If there was no previous halted head, the current head returns the value it has reached and deactivates all active heads. Every time a head reaches a delimiter(the task's case- a space) a new head would be activated.
The presented version here is not the latest, since that one was borked and I hadn't discovered the miracle of GitHub yet.
The task description is as follows(Bulgarian):

TL;DR: Anti- spam based on a dictionary of PHRASES(hence " " being a legit character of the trie dictionary) with set values


�������� ��������, ����� ������ ���� ��������� �� ��������� ��� ��������� ����� �� ������� (���� ���). ������� ���� ������������ ������ �� ���� ��� �����. ��������� �������, ��������� � ������ �� ����� �������� ����� � ��������. �� ����� ������� �� ������� � ������ ������ - ���� ����� (���� � �����������). �� ������� ���������� �� ������������� �� ������ ��� ����������� �� ������� - �������� ���� ��� ����� �� ������������ ��� ���� �����. ����� ����� � �� ��� ���.

������� ��������� ����� �� �������, ����� �������� �����. ������ �� ���������� �� ����� �� ��� � ����� ���������� ���������� �� ����������� �� �������. ���� ����� ���� �� ������� ������ ���� / ����� �� ������, ����� �� � �������. ����� ����� ���� �� ������� �� ������ �� ���� � ������ �� ������� � ���� �� ����. ��������� �� � ������������ ��� �����/������ ����� � ��� � ������� ������� ������� ��������, �� � ������ ���� �� ��� ��������� ���������� ������ ������ - ��������, ��� ��� ��� ���������,  �� ���� ����. ���� ���� �� ���������� ����� ������ �� ��� ������, �������� �� ����� �� �� ���� ����������.

������ ���������� �� ������ � ������ �� ������ ����������� �� ���������� � ������� �����, �������� �� ���� ���� � ������.

��� ������ �� �������� �� ����������� ����� ������� �� ���������, �������� �� ���������� �� ����������, ����� �� ������� ���.

��� � ������ ��� ������� ����� � ��� ������� � ������� ������ �� �� ���������� ���-�������. 

��� � ������� ��� �������� ������� selection sort � sort algorithm, �� ���� algorithm � � ������ ����� selection sort algorithm (�.�. �����, ����� �� �����������) ������ �������� ������ �� ������ ������� ���� �� selection sort (������ �������� �����).

������ �� ���������� ��������, � ����� �����/������ �������� �� ���������� ������ �� �� �� �� ������� � �������. ����� �� ������ � ������� �� � ���������� ��-������ �� ����� �����. 


�������� ������:

algorithm          10
selection sort    20
linked list           20
program            5
viagra                -100

�������� ����:
The selection sort algorithm could be applied to linked lists.

������ �� ������ ������:
3

���������:
�������� �� �������� �� ������ selection sort � algorithm, ��� ���� linked list �� �� ���������� (���� ������� ������ �����). ����� ���� ���� � 10. ���� �������� � (20 + 10) / 10 = 3