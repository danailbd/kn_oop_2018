Какво включи упражнението:
* Принцип за единична отговорност - TODO link
* Визуализация на неща
    * говорихме си малко за MVC - TODO link
* Принцип за Отваряне и Затваряне - TODO link
* Започнахме да мислим в посока, че няма да е лошо да опитахме да добавим нова функционалност към съществуващ код, както и да го пооправим


## Електронен Магазин (music)
Вече се започнахме да създаваме наш собствен електронен магазин [тук](https://github.com/danailbd/kn_oop_2018/tree/master/ex7). Имаме подобрен [код](https://github.com/danailbd/kn_oop_2018/tree/master/ex7/main.cpp) да него, който е добре всеки да разгледа.


## Duolingo
Вече се занимавахме и с опростена реализация на приложение за изучаване на чужди езици. Първоначалните ни изисквания бяха изключително опростени и могат да бъдат намерени [тук](https://github.com/danailbd/kn_oop_2018/tree/master/ex4). Задачата ни сега ще е да разширим тази идея добавяйки нови функционалности:
* Различен тип въпроси - досега имахме единствено въпроси, на които се отговаря в писмен вид. Задачата ни сега ще е да разширим това поведение, добавяйки нов вид въпроси: „Изберете едно от изброениете“ или така наречения „Radio button“. Как ще изглежда това?
    * в какъв вид ще го представим? - може би отделен клас? А какво ще се случи с другия тип въпроси, който поддържаме?
    * как ще добавяме такива въпроси в тестовете ни?
    * как ще визуализираме подобни въпроси?
    * как ще се проверяват отговорите на тези въпроси?
    * А ако искаме да добавим и още типове въпроси, като напримен с избиране на няколко отговора? Или подреждане на изречение по думи? ... Или такива с картинки?
* Няма да е лошо да помислим за по-добра инфраструктура за въпросите:
    * кой се грижи за създаването или промяната на въпроси?
    * кой се грижи за проверката на отговорите на въпросите? А ако искаме да подобрим алгоритмите за проверка на въпроси (например позволяване на малки грешки в записа на думите... изпусната буква, разменени букви и т.н.), **без да пипаме самите модели** (Question класа е модел)?
* Нещо друго, което да добавим? - Акаунти, по-сложна логика за генериране на тестове, звук... Чувствайте се свободни да допълвате и обсъждате.

Много полезно би било да започнете отначало (да пренапишете всичко).

Примерен код може да намерите [тук](https://github.com/danailbd/kn_oop_2018/tree/master/ex7)