# SpamFilter
This is pretty much a Trie built for the Data Structures and Algorithms class' homework. The task was to create an anti- spam filter based on a dictionary of PHRASES(hence " " being a legit character of the trie dictionary) with given values.

My idea sprung out 8 hours before I had to send the homework in. The idea is to have "reading heads", which would move according to the read letter and in case of a match to a word in the dictionary, to stop and check whether there is a head that was activated before the current one that is still working. If there was no previous halted head, the current head returns the value it has reached and deactivates all active heads. Every time a head reaches a delimiter(the task's case- a space) a new head would be activated.
The presented version here is not the latest, since that one was borked and I hadn't discovered the miracle of GitHub yet.

The task description is as follows(Bulgarian):

Напишете програма, която приема като аргументи от командния ред множество имена на файлове (поне два). Първият файл представлява речник от думи или фрази. Валидните символи, участващи в думите са малки латински букви и интервал. За всеки елемент от речника е дадена оценка - цяло число (може и отрицателно). То показва коефициент на принадлежност на думата към категорията на речника - например спам или текст за програмиране или нещо друго. Всяка фраза е на нов ред.

Следват множество имена на файлове, всеки съдържащ текст. Трябва да определите за всеки от тях с какъв коефициент принадлежи на категорията на речника. Това става като се намерят всички думи / фрази от текста, които са в речника. Всяка фраза може да започва от начало на дума и трябва да завърши в края на дума. Търсенето не е чувствително към малки/главни букви и ако в речника фразата съдържа интервал, то в текста може да има съответен произволен празен символ - интервал, нов ред или табулация,  но само един. След края на намерената фраза трябва да има символ, различен от буква за да бъде разпозната.

Общият коефициент на текста е сумата от всички коефициенти на намерените в речника фрази, разделен на броя думи в текста.

Вие трябва да изведете на стандартния изход имената на файловете, следвани от съответния им коефициент, всеки на отделен ред.

Ако в текста има няколко фрази с общ префикс в речника трябва да се предпочете най-дългата. 

Ако в речника има например фразите selection sort и sort algorithm, но няма algorithm и в текста имате selection sort algorithm (т.е. фрази, които се припокриват) вашата програма трябва да отчете срещане само на selection sort (първат срещната фраза).

Трябва да съобразите варианта, в който някои/всички текстове са достатъчно големи за да не се съберат в паметта. Всяка от думите в речника ще е значително по-кратка от целия текст. 


Примерен речник:

algorithm          10
selection sort    20
linked list           20
program            5
viagra                -100

Примерен файл:
The selection sort algorithm could be applied to linked lists.

Оценка по горния речник:
3

Обяснение:
Оценката се получава от думите selection sort и algorithm, тъй като linked list не се разпознава (след фразата следва буква). Общия брой думи е 10. Така оценката е (20 + 10) / 10 = 3
