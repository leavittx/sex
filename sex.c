/*sex.c*/

/* Original author unknown.  Presumably this is public domain by now.
 * If you are the original author or know the original author, please
 * contact <freebsd@spatula.net>
 * 
 * Orphan code cleaned up a bit by Nick Johnson <freebsd@spatula.net>
 * Completely rewrote how word wrapping works and added -w flag.
 * 
 * Russian language added by Lev Panov <lev.panov@gmail.comS>
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

/*
static char     *faster[] = {
  "\"Let the games begin!\"",             "\"Sweet Jesus!\"",
  "\"Not that!\"",                        "\"At last!\"",
  "\"Land o' Goshen!\"",                  "\"Is that all?\"",
  "\"Cheese it, the cops!\"",             "\"I never dreamed it could be\"",
  "\"If I do, you won't respect me!\"",   "\"Now!\"",
  "\"Open sesame!\"",                     "\"EMR!\"",
  "\"Again!\"",                           "\"Faster!\"",
  "\"Harder!\"",                          "\"Help!\"",
  "\"Fuck me harder!\"",                  "\"Is it in yet?\"",
  "\"You aren't my father!\"",            "\"Doctor, that's not *my* shou\"",
  "\"No, no, do the goldfish!\"",         "\"Holy Batmobile, Batman!\"",
  "\"He's dead, he's dead!\"",            "\"Take me, Robert!\"",
  "\"I'm a Republican!\"",                "\"Put four fingers in!\"",
  "\"What a lover!\"",                    "\"Talk dirty, you pig!\"",
  "\"The ceiling needs painting,\"",      "\"Suck harder!\"",
  "\"The animals will hear!\"",           "\"Not in public!\"",
};
*/
static char     *faster[] = {
  "\"Давай скорее!\"", "\"Святой Иисус!\"",
  "\"Не туда!\"", "\"Наконец-то!\"",
  "\"O Земля Гошена!\"", "\"И это все??\"",
  "\"Не останавливайся!\"", "\"Я никогда не думала, что такое возможно\"",
  "\"Если я сделаю это, вы не будете уважать меня!\"", "\"Давай сейчас!\"",
  "\"Сезам, откройся!\"", "\"Выеби меня как шлюшку!\"",
  "\"Ещё!\"", "\"Быстрее!\"",
  "\"Пяль меня жестче!\"", "\"Помогите!\"",
  "\"Трахни меня сильнее!\"", "\"Он ещё внутри?\"",
  "\"Ты мне не отец!\"", "\"Доктор, это не *моё* шоу\"",
  "\"Нет, нет, сделай золотую рыбку!\"", "\"Святой Бэтмобиль!\"",
  "\"Он мертв, он мертв!\"", "\"Возьми меня, Иван!\"",
  "\"Я Республиканка!\"", "\"Засунь внутрь четыре пальца!\"",
  "\"Какой любовник!\"", "\"Обругай меня, ты, свинья!\"",
  "\"Потолок нуждается в покраске,\"", "\"Соси сильнее!\"",
  "\"Животные услышат это!\"", "\"Не на людях!\"",
};

/*
static char     *said[] = {
        "bellowed",             "yelped",               "croaked",
        "growled",              "panted",               "moaned",
        "grunted",              "laughed",              "warbled",
        "sighed",               "ejaculated",           "choked",
        "stammered",            "wheezed",              "squealed",
        "whimpered",            "salivated",            "tongued",
        "cried",                "screamed",             "yelled",
        "said",
};
*/
static char     *said[] = {
		"взревела", "визгнула", "крякнула",
        "Буркнула","вскрикнула","застонала",
        "взмолилась", "засмеялась", "всхлипнула",
        "вздохнула", "воскликнула", "задыхаясь простонала",
        "пробормотала", "засопела", "завизжала",
        "заскулила", "взмолилась", "прошептала",
        "закричала", "кричала", "воскрикнула",
        "сказала",
};

/*
static char     *the[] = {
        "the",
};
*/
static char     *the[] = {
        "",
};

/*
static char     *fadj[] = {
        "saucy",                "wanton",               "unfortunate",
        "lust-crazed",          "nine-year-old",        "bull-dyke",
        "bisexual",             "gorgeous",             "sweet",
        "nymphomaniacal",       "large-hipped",         "freckled",
        "forty-five year old",  "white-haired",         "large-boned",
        "saintly",              "blind",                "bearded",
        "blue-eyed",            "large tongued",        "friendly",
        "piano playing",        "ear licking",          "doe eyed",
        "sock sniffing",        "lesbian",              "hairy",
};
*/
static char     *fadj[] = {
	    "симпотичная", "толстая", "невезучая",
        "похотливо-сумасшедшая", "девятилетняя", "быкообразная",
        "Бисексуальная", "великолепная", "сладкая",
        "нимфоподобная", "большегрудая", "веснушчатая",
        "сорокапятилетняя", "светловолосая", "костлявая",
        "святая", "слепая", "бородатая",
        "синеокоая", "длинноязыкая", "дружественная",
        "играющая на пианино", "лижущая ухо", "большеглазая",
        "нюхающая носки", "лесбиянистая", "волосатая",
};

/*
static char     *female[] = {
   "baggage",              "hussy",                "woman",
   "Duchess",              "female impersonator",  "nymphomaniac",
   "virgin",               "leather freak",        "home-coming queen",
   "defrocked nun",        "bisexual budgie",      "cheerleader",
   "office secretary",     "sexual deviate",       "DARPA contract monitor",
   "little matchgirl",     "ceremonial penguin",   "femme fatale",
   "bosses' daughter",     "construction worker",  "sausage abuser",
   "secretary",            "Congressman's page",   "grandmother",
   "penguin",              "German shepherd",      "stewardess",
   "waitress",             "prostitute",           "computer science group",
   "housewife",
};
*/
static char     *female[] = {
	"блядь", "шлюха", "женщина",
	"герцогиня", "женщина-двойник", "нимфоманка",
	"девственница", "хуесоска", "вернувшаяся королева",
	"бывшая монахиня", "бисексуальная волнистая попугаиха", "участница группы поддержки",
	"секретарь офиса", "ёбырша", "наёбщица",
	"девочка со спичками", "торжественная пингвиниха", "роковая женщина",
	"дочка босса", "строительница", "обидчица колбасы",
	"секретарша", "тварь", "бабушка",
	"пингвиниха", "Немецкая овчарка", "стюардесса",
	"официантка", "проститутка", "сучка",
	"домохозяйка",
};

/*
static char     *asthe[] = {
        "as the",
};
*/
static char     *asthe[] = {
        "когда",
        "в то время, как",
};

/*
static char     *madjec[] = {
   "thrashing",            "slurping",             "insatiable",
   "rabid",                "satanic",              "corpulent",
   "nose-grooming",        "tripe-fondling",       "dribbling",
   "spread-eagled",        "orally fixated",       "vile",
   "awesomely endowed",    "handsome",             "mush-brained",
   "tremendously hung",    "three-legged",         "pile-driving",
   "cross-dressing",       "gerbil buggering",     "bung-hole stuffing",
   "sphincter licking",    "hair-pie chewing",     "muff-diving",
   "clam shucking",        "egg-sucking",          "bicycle seat sniffing",
};
*/
static char     *madjec[] = {
	"Обмолота", "прихлебывая", "ненасытный",
	"Бешеный", "сатанинской", "тучный",
	"Нос уход", "чушь-ласки", "ведением",
	"Распластанный", "устно зафиксирован", "гнусной",
	"Грозно наделены", "красивый", "грибы мозгом",
	"Висел огромный", "три ноги", "сваебойной",
	"Кросс-одевания", "песчанка buggering", "пробкой отверстие начинкой",
	"Сфинктера лизать", "волосы пирог жевательных", "муфта-дайвинг",
	"Моллюск вытаскивания", "яйцо-сосать", "велосипед место нюхают",
};

/*
static char     *male[] = {
   "rakehell",             "hunchback",            "lecherous lickspittle",
   "archduke",             "midget",               "hired hand",
   "great Dane",           "stallion",             "donkey",
   "electric eel",         "paraplegic pothead",   "dirty old man",
   "faggot butler",        "friar",                "black-power advocate",
   "follicle fetishist",   "handsome priest",      "chicken flicker",
   "homosexual flamingo",  "ex-celibate",          "drug sucker",
   "ex-woman",             "construction worker",  "hair dresser",
   "dentist",              "judge",                "social worker",
};
*/
static char     *male[] = {
	"развратник", "горбун", "развратный холуй",
	"эрцгерцог", "карлик", "наёмник",
	"великий Лука", "жеребец", "осёл",
	"электрический угорь", "парализованный хуйбан", "грязный старик",
	"дворецкий педика", "монах", "защитник черные сил",
	"фетишист-фолликула", "красивый священник", "легатель куриц",
	"гомосексуальный фламинго", "экс-холостяк", "наркосос",
	"экс-женщина", "строитель", "парикмахер",
	"стоматолог", "судья", "социальный работник",
};

/*
static char     *diddled[] = {
   "diddled",              "devoured",             "fondled",
   "mouthed",              "tongued",              "lashed",
   "tweaked",              "violated",             "defiled",
   "irrigated",            "penetrated",           "ravished",
   "hammered",             "bit",                  "tongue slashed",
   "sucked",               "fucked",               "rubbed",
   "grudge fucked",        "masturbated with",     "slurped",
};
*/
static char     *diddled[] = {
	"совал", "пожирал", "приласкал",
	"пихал", "тянул", "хлестал",
	"подстраивал", "переносил", "осквернил",
	"орошал", "проник", "изнасиловал",
	"забил", "ел", "просовывал",
	"сосать", "трахал", "тер",
	"трахал с обиды", "дрочил с", "отхлебнул",
};

/*
char *her[] = {
        "her",
};
*/
char *her[] = {
        "её",
};

/*
static char     *titadj[] = {
        "alabaster",            "pink-tipped",          "creamy",
        "rosebud",              "moist",                "throbbing",
        "juicy",                "heaving",              "straining",
        "mammoth",              "succulent",            "quivering",
        "rosey",                "globular",             "varicose",
        "jiggling",             "bloody",               "tilted",
        "dribbling",            "oozing",               "firm",
        "pendulous",            "muscular",             "bovine",
};
*/
static char     *titadj[] = {
	    "Алебастр", "розовый наконечником", "сливочное",
        "Бутон розы", "влажная", "пульсация",
        "Пикантное", "вздымается", "напряжение",
        "Мамонт", "сочные", "дрожали",
        "Рози", "шаровых", "варикозной",
        "Переустройства", "кровавый", "наклон",
        "Ведением", "просачивание", "фирма",
        "Подвешенный", "мускулистый", "бычьим",
};

/*
static char     *knockers[] = {
        "globes",               "melons",               "mounds",
        "buds",                 "paps",                 "chubbies",
        "protuberances",        "treasures",            "buns",
        "bung",                 "vestibule",            "armpits",
        "tits",                 "knockers",             "elbows",
        "eyes",                 "hooters",              "jugs",
        "lungs",                "headlights",           "disk drives",
        "bumpers",              "knees",                "fried eggs",
        "buttocks",             "charlies",             "ear lobes",
        "bazooms",              "mammaries",
};
*/
static char     *knockers[] = {
	    "Глобусы", "дыни", "курганов",
        "Почки", "перси", "chubbies",
        "Протуберанцы", "сокровища", "булочки",
        "Пробка", "передняя", "мышками",
        "Сиськи", "колотушки", "колена",
        "Глаза", "сиськи", "кувшины",
        "Легкие", "фары", "диски",
        "Бамперы", "колен", "яичница",
        "Ягодицы", "Чарли", "мочки уха",
        "Bazooms", "mammaries",
};

/*
char *and[] = {
        "and",
};
*/
char *and[] = {
        "и",
};

/*
static char     *thrust[] = {
        "plunged",              "thrust",               "squeezed",
        "pounded",              "drove",                "eased",
        "slid",                 "hammered",             "squished",
        "crammed",              "slammed",              "reamed",
        "rammed",               "dipped",               "inserted",
        "plugged",              "augured",              "pushed",
        "ripped",               "forced",               "wrenched",
};
*/
static char     *thrust[] = {
	    "Погрузился", "тяги", "сжал",
        "Стучал", "поехали", "облегчил",
        "Скользнул", "забил", "сплющенным",
        "Забиты", "хлопнул", "рассверленный",
        "Протаранил", "ближнего", "включить",
        "Подключен", "сулила", "толкнул",
        "Разорвал", "вынуждены", "оторвал",
};

/*
static char     *his[] = {
        "his",
};
*/
static char     *his[] = {
        "его",
};

/*
static char     *dongadj[] = {
        "bursting",             "jutting",              "glistening",
        "Brobdingnagian",       "prodigious",           "purple",
        "searing",              "swollen",              "rigid",
        "rampaging",            "warty",                "steaming",
        "gorged",               "trunklike",            "foaming",
        "spouting",             "swinish",              "prosthetic",
        "blue veined",          "engorged",             "horse like",
        "throbbing",            "humongous",            "hole splitting",
        "serpentine",           "curved",               "steel encased",
        "glass encrusted",      "knobby",               "surgically altered",
        "metal tipped",         "open sored",           "rapidly dwindling",
        "swelling",             "miniscule",            "boney",
};
*/
static char     *dongadj[] = {
	    "Разрыва", "выступающий", "блестящий",
        "Brobdingnagian", "огромный", "пурпурной",
        "Жгучая", "опухшие", "жесткая",
        "Неистовый", "бородавчатые", "пар",
        "Наелись", "trunklike", "пены",
        "Фонтанирования", "свинский", "протез",
        "Синих прожилках", "наполненный", "лошедеподобный",
        "Пульсация", "Humongous", "расщепляющий дыры",
        "Серпантин", "кривой", "стальной корпус",
        "Стеклянный инкрустированный", "бугристая", "хирургически измененных",
        "Металл наконечником", "открыто sored", "становится все меньше",
        "Вздутие", "незначительный", "Бони",
};

/*
static char     *dong[] = {
   "intruder",             "prong",                "stump",
   "member",               "meat loaf",            "majesty",
   "bowsprit",             "earthmover",           "jackhammer",
   "ramrod",               "cod",                  "jabber",
   "gusher",               "poker",                "engine",
   "brownie",              "joy stick",            "plunger",
   "piston",               "tool",                 "manhood",
   "lollipop",             "kidney prodder",       "candlestick",
   "John Thomas",          "arm",                  "testicles",
   "balls",                "finger",               "foot",
   "tongue",               "dick",                 "one-eyed wonder worm",
   "canyon yodeler",       "middle leg",           "neck wrapper",
   "stick shift",          "dong",                 "Linda Lovelace choker",
};
*/
static char     *dong[] = {
	"Злоумышленником", "контакт", "пень",
	"Член", "буханка мяса", "великан",
	"Бушприт", "землеройная машина", "отбойного молотка",
	"Палка", "трески", "Jabber",
	"Фонтан", "покер", "двигатель",
	"Домовой", "палка радости", "Поршень",
	"Поршень", "инструмент", "зрелость",
	"Lollipop", "почки prodder", "светильник",
	"Джон Томас", "рука", "яички",
	"Шары", "палец", "нога",
	"Языка", "член", "одноглазый удивительно червя",
	"Каньона йодлер", "среднюю ногу", "шеи оболочку",
	"Кнута сдвиг", "дон", "Линда Лавлейс галстук",
};

/*
static char     *intoher[] = {
        "into her",
};
*/
static char     *intoher[] = {
        "в её",
        "внутрь её"
};

/*
static char     *twatadj[] = {
        "pulsing",              "hungry",               "hymeneal",
        "palpitating",          "gaping",               "slavering",
        "welcoming",            "glutted",              "gobbling",
        "cobwebby",             "ravenous",             "slurping",
        "glistening",           "dripping",             "scabiferous",
        "porous",               "soft-spoken",          "pink",
        "dusty",                "tight",                "odiferous",
        "moist",                "loose",                "scarred",
        "weapon-less",          "banana stuffed",       "tire tracked",
        "mouse nibbled",        "tightly tensed",       "oft traveled",
        "grateful",             "festering",
};
*/
static char     *twatadj[] = {
	    "Пульсирующей", "голодный", "брачный",
        "Животрепещущий", "зияющие", "слюнявый",
        "Приветствовать", "переполнен", "сожрать",
        "Паутина", "голодный", "прихлебывая",
        "Блестящий", "мокрый", "scabiferous",
        "Пористой", "тихий", "розовый",
        "Пыльной", "жесткий", "odiferous",
        "Влажной", "свободные", "шрамы",
        "Оружие-менее", "банан чучела", "шин отслеживаются",
        "Мышь грызла", "плотно напряженной", "часто путешествовал",
        "Благодарные", "гнойный",
};

/*
static char     *twat[] = {
        "swamp.",               "honeypot.",            "jam jar.",
        "butterbox.",           "furburger.",           "cherry pie.",
        "cush.",                "slot.",                "slit.",
        "cockpit.",             "damp.",                "furrow.",
        "sanctum sanctorum.",   "bearded clam.",        "continental divide.",
        "paradise valley.",     "red river valley.",    "slot machine.",
        "quim.",                "palace.",              "ass.",
        "rose bud.",            "throat.",              "eye socket.",
        "tenderness.",          "inner ear.",           "orifice.",
        "appendix scar.",       "wound.",               "navel.",
        "mouth.",               "nose.",                "cunt.",
};
*/
static char     *twat[] = {
	    "Болото.", "Приманка.", "Варенье банке.",
        "Butterbox.", "Furburger.", "Вишневого пирога.",
        "Куш.", "Гнездо.", "Щели.",
        "Кабины.", "Сыро.", "Борозду.",
        "Святая святых.", "Бородатый моллюсков.", "Континентальный пропасти.",
        "Paradise Valley.", "Красный долину реки.", "Слот-машина.",
        "Манда.", "Дворец.", "Осел.",
        "Бутон розы.", "В горле.", "Глаз.",
        "Нежность.", "Внутреннее ухо.", "Устье.",
        "Добавление шрам.", "Раны.", "Пуп.",
        "Рот.", "Нос.", "Пизда.",
};

struct table {
        char    **item;
        short   len;
};

typedef struct table    TABLE;
#define SZ(a)           sizeof(a) / sizeof(char *)

TABLE   list[] = {
        {faster,         SZ(faster)},     {said,           SZ(said)},
        {the,            SZ(the)},        {fadj,           SZ(fadj)},
        {female,         SZ(female)},     {asthe,          SZ(asthe)},
        {madjec,         SZ(madjec)},     {male,           SZ(male)},
        {diddled,        SZ(diddled)},    {her,            SZ(her)},
        {titadj,         SZ(titadj)},     {knockers,       SZ(knockers)},
        {and,            SZ(and)},        {thrust,         SZ(thrust)},
        {his,            SZ(his)},        {dongadj,        SZ(dongadj)},
        {dong,           SZ(dong)},       {intoher,        SZ(intoher)},
        {twatadj,        SZ(twatadj)},    {twat,           SZ(twat)},
        {(char **)NULL,  (int)NULL},
};

#define LLINE   50
static short    lwidth;
static short    wraplen;

int main(int argc, char **argv)
{
   register TABLE  *ttp;
   register char   *cp;
   int     getpid();
   long     now;
   char buffer[2048];
   int pos, lastword;

   wraplen = 0;
   if (argc > 1) {
	if (!strcmp(argv[1],"-w")) {
	    if (argc == 3) {
		wraplen = atoi(argv[2]);
	    } else {
		wraplen = LLINE;
	    }
	}
   }

   now = time(&now) / random();
   srandom(getpid() + (int)((now >> 16) + now + time(&now)));

   pos = lastword = 0;
   for (ttp = list;ttp->item;++ttp,++lwidth) {
      for (cp = ttp->len > 1 ? ttp->item[random() % ttp->len] :
           *ttp->item;*cp;++cp,++lwidth) {
	buffer[pos] = *cp;
	if ((wraplen > 0) && (lwidth >= wraplen)) {
	    buffer[lastword] = '\n';
	    lwidth = pos - lastword;
	}
	if (isspace(*cp)) {
	    lastword = pos;
	} 
	pos++;
      }
      buffer[pos] = ' ';
      lastword = pos++;
   }
   buffer[pos] = '\0';

   puts(buffer);

   return(0);
}
