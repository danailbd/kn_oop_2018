Съвети (колкото и да е лошо даването на съвети):
Ето малко полезни принципи, на които да обръщате внимание:
- http://www.oodesign.com/design-principles.html - от тук засега обърнете внимание на Open-Close и Single responsibility. Опитвайте се един по един да ги включвате във вашия дизайн (проектиране).
- KISS - keep it simple silly - не усложнявайте прекалено нещата, каквото и да правите... все пак трябва да можете да разберете какво сте правили, ако си погледнете кода след няколко седмици
- DRY - do not repeat yourself - ако виждате парчета еднакъв код, вероятно има начин да ги обедините - обща променлива, обща функция... или може би абстракция

Пишете вашият код така, че да може напълно случаен човек, по възможност с програмистки познания, да може да рабере вашият код и да прави промени по него. Коментари, документация и най-вече с смислени имена на фукции, променливи... като цяло на всичко.


### Bickie Shop
 
Днес ще си направим собствен електронен магазин... или поне начална версия на такъев. Нашият магазин ще разполага с артикули и ще можем да правим поръчки през него. Какво ще искаме по-точно:
- да добавяме артикули към машия магазин
- да премахваме такива (вече не са налични)
- да показваме (list-ваме) всички артикули в магазина в момента
- да може да се направи поръчка на артикул
Ограничения:
- За сега поръчките ще са във вид на наложен платеж - не разполагаме с възможност за заплащане online
- Ще можем да поръчваме само по един артикул за една поръчка

Вие преценете каква информация за различните обекти ви е необходима. Няма нужда да бъдете безкрайно детайлни, но нека информацията е достъчно близко до реалността.


Помислете си за визуализацията на нашия магазин - опитайте се да разделите визуализацията от самото управление на магазина. Подобно разделение би улеснило промяната на визуализацията, без нужда от промяна на модула за управление.
Помислете също как бихме могли да улесним клиентите си, като им спестим въвеждането на тяхната информация при всяка поръчка. (може би акаунт?)

