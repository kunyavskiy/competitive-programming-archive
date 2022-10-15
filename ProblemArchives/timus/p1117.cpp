#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
    #define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int BL = 1000000;

ll ans[] = {0LL,999986LL, 1999986LL, 2999980LL, 3999986LL, 4999984LL, 5999980LL, 6999976LL, 7999986LL, 8999986LL, 9999984LL, 10999978LL, 11999980LL, 12999980LL, 13999976LL, 14999980LL, 15999986LL, 16999984LL, 17999986LL, 18999980LL, 19999984LL, 20999982LL, 21999978LL, 22999972LL, 23999980LL, 24999976LL, 25999980LL, 26999972LL, 27999976LL, 28999982LL, 29999980LL, 30999980LL, 31999986LL, 32999976LL, 33999984LL, 34999982LL, 35999986LL, 36999982LL, 37999980LL, 38999978LL, 39999984LL, 40999980LL, 41999982LL, 42999988LL, 43999978LL, 44999978LL, 45999972LL, 46999978LL, 47999980LL, 48999974LL, 49999976LL, 50999982LL, 51999980LL, 52999978LL, 53999972LL, 54999974LL, 55999976LL, 56999982LL, 57999982LL, 58999984LL, 59999980LL, 60999980LL, 61999980LL, 62999978LL, 63999986LL, 64999972LL, 65999976LL, 66999970LL, 67999984LL, 68999978LL, 69999982LL, 70999972LL, 71999986LL, 72999980LL, 73999982LL, 74999980LL, 75999980LL, 76999976LL, 77999978LL, 78999976LL, 79999984LL, 80999974LL, 81999980LL, 82999974LL, 83999982LL, 84999976LL, 85999988LL, 86999976LL, 87999978LL, 88999984LL, 89999978LL, 90999978LL, 91999972LL, 92999982LL, 93999978LL, 94999976LL, 95999980LL, 96999982LL, 97999974LL, 98999972LL, 99999976LL, 100999984LL, 101999982LL, 102999976LL, 103999980LL, 104999984LL, 105999978LL, 106999982LL, 107999972LL, 108999972LL, 109999974LL, 110999972LL, 111999976LL, 112999974LL, 113999982LL, 114999976LL, 115999982LL, 116999974LL, 117999984LL, 118999972LL, 119999980LL, 120999980LL, 121999980LL, 122999976LL, 123999980LL, 124999974LL, 125999978LL, 126999972LL, 127999986LL, 128999980LL, 129999972LL, 130999970LL, 131999976LL, 132999970LL, 133999970LL, 134999974LL, 135999984LL, 136999982LL, 137999978LL, 138999980LL, 139999982LL, 140999974LL, 141999972LL, 142999986LL, 143999986LL, 144999984LL, 145999980LL, 146999982LL, 147999982LL, 148999978LL, 149999980LL, 150999986LL, 151999980LL, 152999980LL, 153999976LL, 154999976LL, 155999978LL, 156999978LL, 157999976LL, 158999976LL, 159999984LL, 160999980LL, 161999974LL, 162999972LL, 163999980LL, 164999974LL, 165999974LL, 166999972LL, 167999982LL, 168999980LL, 169999976LL, 170999984LL, 171999988LL, 172999976LL, 173999976LL, 174999976LL, 175999978LL, 176999978LL, 177999984LL, 178999976LL, 179999978LL, 180999974LL, 181999978LL, 182999974LL, 183999972LL, 184999982LL, 185999982LL, 186999978LL, 187999978LL, 188999976LL, 189999976LL, 190999974LL, 191999980LL, 192999980LL, 193999982LL, 194999968LL, 195999974LL, 196999966LL, 197999972LL, 198999966LL, 199999976LL, 200999976LL, 201999984LL, 202999982LL, 203999982LL, 204999982LL, 205999976LL, 206999978LL, 207999980LL, 208999978LL, 209999984LL, 210999976LL, 211999978LL, 212999976LL, 213999982LL, 214999978LL, 215999972LL, 216999976LL, 217999972LL, 218999976LL, 219999974LL, 220999980LL, 221999972LL, 222999974LL, 223999976LL, 224999976LL, 225999974LL, 226999970LL, 227999982LL, 228999978LL, 229999976LL, 230999974LL, 231999982LL, 232999976LL, 233999974LL, 234999982LL, 235999984LL, 236999982LL, 237999972LL, 238999970LL, 239999980LL, 240999972LL, 241999980LL, 242999970LL, 243999980LL, 244999974LL, 245999976LL, 246999970LL, 247999980LL, 248999974LL, 249999974LL, 250999968LL, 251999978LL, 252999976LL, 253999972LL, 254999968LL, 255999986LL, 256999980LL, 257999980LL, 258999978LL, 259999972LL, 260999974LL, 261999970LL, 262999970LL, 263999976LL, 264999974LL, 265999970LL, 266999974LL, 267999970LL, 268999984LL, 269999974LL, 270999982LL, 271999984LL, 272999982LL, 273999982LL, 274999982LL, 275999978LL, 276999980LL, 277999980LL, 278999980LL, 279999982LL, 280999974LL, 281999974LL, 282999974LL, 283999972LL, 284999978LL, 285999986LL, 286999978LL, 287999986LL, 288999978LL, 289999984LL, 290999978LL, 291999980LL, 292999974LL, 293999982LL, 294999974LL, 295999982LL, 296999974LL, 297999978LL, 298999980LL, 299999980LL, 300999976LL, 301999986LL, 302999976LL, 303999980LL, 304999974LL, 305999980LL, 306999978LL, 307999976LL, 308999972LL, 309999976LL, 310999974LL, 311999978LL, 312999988LL, 313999978LL, 314999980LL, 315999976LL, 316999980LL, 317999976LL, 318999978LL, 319999984LL, 320999984LL, 321999980LL, 322999980LL, 323999974LL, 324999972LL, 325999972LL, 326999966LL, 327999980LL, 328999980LL, 329999974LL, 330999974LL, 331999974LL, 332999974LL, 333999972LL, 334999968LL, 335999982LL, 336999980LL, 337999980LL, 338999976LL, 339999976LL, 340999974LL, 341999984LL, 342999976LL, 343999988LL, 344999986LL, 345999976LL, 346999974LL, 347999976LL, 348999978LL, 349999976LL, 350999970LL, 351999978LL, 352999980LL, 353999978LL, 354999974LL, 355999984LL, 356999976LL, 357999976LL, 358999970LL, 359999978LL, 360999980LL, 361999974LL, 362999976LL, 363999978LL, 364999976LL, 365999974LL, 366999964LL, 367999972LL, 368999966LL, 369999982LL, 370999980LL, 371999982LL, 372999974LL, 373999978LL, 374999976LL, 375999978LL, 376999980LL, 377999976LL, 378999976LL, 379999976LL, 380999974LL, 381999974LL, 382999974LL, 383999980LL, 384999976LL, 385999980LL, 386999978LL, 387999982LL, 388999970LL, 389999968LL, 390999970LL, 391999974LL, 392999974LL, 393999966LL, 394999974LL, 395999972LL, 396999970LL, 397999966LL, 398999978LL, 399999976LL, 400999972LL, 401999976LL, 402999982LL, 403999984LL, 404999976LL, 405999982LL, 406999980LL, 407999982LL, 408999982LL, 409999982LL, 410999970LL, 411999976LL, 412999976LL, 413999978LL, 414999974LL, 415999980LL, 416999974LL, 417999978LL, 418999970LL, 419999984LL, 420999972LL, 421999976LL, 422999970LL, 423999978LL, 424999974LL, 425999976LL, 426999978LL, 427999982LL, 428999982LL, 429999978LL, 430999978LL, 431999972LL, 432999974LL, 433999976LL, 434999972LL, 435999972LL, 436999980LL, 437999976LL, 438999974LL, 439999974LL, 440999984LL, 441999980LL, 442999974LL, 443999972LL, 444999980LL, 445999974LL, 446999974LL, 447999976LL, 448999978LL, 449999976LL, 450999972LL, 451999974LL, 452999980LL, 453999970LL, 454999966LL, 455999982LL, 456999976LL, 457999978LL, 458999972LL, 459999976LL, 460999972LL, 461999974LL, 462999974LL, 463999982LL, 464999970LL, 465999976LL, 466999968LL, 467999974LL, 468999968LL, 469999982LL, 470999976LL, 471999984LL, 472999980LL, 473999982LL, 474999970LL, 475999972LL, 476999974LL, 477999970LL, 478999972LL, 479999980LL, 480999972LL, 481999972LL, 482999968LL, 483999980LL, 484999978LL, 485999970LL, 486999976LL, 487999980LL, 488999978LL, 489999974LL, 490999982LL, 491999976LL, 492999976LL, 493999970LL, 494999978LL, 495999980LL, 496999968LL, 497999974LL, 498999972LL, 499999974LL, 500999970LL, 501999968LL, 502999966LL, 503999978LL, 504999978LL, 505999976LL, 506999976LL, 507999972LL, 508999972LL, 509999968LL, 510999968LL, 511999986LL, 512999976LL, 513999980LL, 514999974LL, 515999980LL, 516999974LL, 517999978LL, 518999964LL, 519999972LL, 520999974LL, 521999974LL, 522999974LL, 523999970LL, 524999970LL, 525999970LL, 526999972LL, 527999976LL, 528999970LL, 529999974LL, 530999970LL, 531999970LL, 532999968LL, 533999974LL, 534999966LL, 535999970LL, 536999984LL, 537999984LL, 538999982LL, 539999974LL, 540999982LL, 541999982LL, 542999978LL, 543999984LL, 544999982LL, 545999982LL, 546999978LL, 547999982LL, 548999980LL, 549999982LL, 550999972LL, 551999978LL, 552999978LL, 553999980LL, 554999984LL, 555999980LL, 556999980LL, 557999980LL, 558999978LL, 559999982LL, 560999980LL, 561999974LL, 562999976LL, 563999974LL, 564999974LL, 565999974LL, 566999970LL, 567999972LL, 568999982LL, 569999978LL, 570999984LL, 571999986LL, 572999980LL, 573999978LL, 574999976LL, 575999986LL, 576999982LL, 577999978LL, 578999978LL, 579999984LL, 580999978LL, 581999978LL, 582999964LL, 583999980LL, 584999976LL, 585999974LL, 586999972LL, 587999982LL, 588999974LL, 589999974LL, 590999972LL, 591999982LL, 592999976LL, 593999974LL, 594999968LL, 595999978LL, 596999970LL, 597999980LL, 598999978LL, 599999980LL, 600999980LL, 601999976LL, 602999976LL, 603999986LL, 604999980LL, 605999976LL, 606999978LL, 607999980LL, 608999980LL, 609999974LL, 610999974LL, 611999980LL, 612999980LL, 613999978LL, 614999978LL, 615999976LL, 616999978LL, 617999972LL, 618999978LL, 619999976LL, 620999978LL, 621999974LL, 622999978LL, 623999978LL, 624999978LL, 625999988LL, 626999974LL, 627999978LL, 628999970LL, 629999980LL, 630999974LL, 631999976LL, 632999976LL, 633999980LL, 634999974LL, 635999976LL, 636999968LL, 637999978LL, 638999974LL, 639999984LL, 640999978LL, 641999984LL, 642999974LL, 643999980LL, 644999972LL, 645999980LL, 646999974LL, 647999974LL, 648999972LL, 649999972LL, 650999972LL, 651999972LL, 652999966LL, 653999966LL, 654999980LL, 655999980LL, 656999980LL, 657999980LL, 658999974LL, 659999974LL, 660999974LL, 661999974LL, 662999976LL, 663999974LL, 664999978LL, 665999974LL, 666999974LL, 667999972LL, 668999980LL, 669999968LL, 670999966LL, 671999982LL, 672999980LL, 673999980LL, 674999972LL, 675999980LL, 676999978LL, 677999976LL, 678999972LL, 679999976LL, 680999976LL, 681999974LL, 682999978LL, 683999984LL, 684999980LL, 685999976LL, 686999974LL, 687999988LL, 688999980LL, 689999986LL, 690999972LL, 691999976LL, 692999974LL, 693999974LL, 694999970LL, 695999976LL, 696999980LL, 697999978LL, 698999974LL, 699999976LL, 700999978LL, 701999970LL, 702999968LL, 703999978LL, 704999980LL, 705999980LL, 706999972LL, 707999978LL, 708999976LL, 709999974LL, 710999970LL, 711999984LL, 712999974LL, 713999976LL, 714999978LL, 715999976LL, 716999974LL, 717999970LL, 718999974LL, 719999978LL, 720999972LL, 721999980LL, 722999978LL, 723999974LL, 724999970LL, 725999976LL, 726999974LL, 727999978LL, 728999974LL, 729999976LL, 730999976LL, 731999974LL, 732999976LL, 733999964LL, 734999968LL, 735999972LL, 736999968LL, 737999966LL, 738999976LL, 739999982LL, 740999978LL, 741999980LL, 742999976LL, 743999982LL, 744999974LL, 745999974LL, 746999980LL, 747999978LL, 748999976LL, 749999976LL, 750999974LL, 751999978LL, 752999972LL, 753999980LL, 754999982LL, 755999976LL, 756999970LL, 757999976LL, 758999968LL, 759999976LL, 760999972LL, 761999974LL, 762999970LL, 763999974LL, 764999972LL, 765999974LL, 766999964LL, 767999980LL, 768999978LL, 769999976LL, 770999972LL, 771999980LL, 772999978LL, 773999978LL, 774999972LL, 775999982LL, 776999982LL, 777999970LL, 778999972LL, 779999968LL, 780999974LL, 781999970LL, 782999972LL, 783999974LL, 784999976LL, 785999974LL, 786999972LL, 787999966LL, 788999972LL, 789999974LL, 790999970LL, 791999972LL, 792999978LL, 793999970LL, 794999970LL, 795999966LL, 796999980LL, 797999978LL, 798999966LL, 799999976LL, 800999970LL, 801999972LL, 802999966LL, 803999976LL, 804999966LL, 805999982LL, 806999974LL, 807999984LL, 808999980LL, 809999976LL, 810999978LL, 811999982LL, 812999976LL, 813999980LL, 814999974LL, 815999982LL, 816999976LL, 817999982LL, 818999976LL, 819999982LL, 820999968LL, 821999970LL, 822999970LL, 823999976LL, 824999984LL, 825999976LL, 826999980LL, 827999978LL, 828999978LL, 829999974LL, 830999980LL, 831999980LL, 832999978LL, 833999974LL, 834999976LL, 835999978LL, 836999972LL, 837999970LL, 838999978LL, 839999984LL, 840999984LL, 841999972LL, 842999974LL, 843999976LL, 844999972LL, 845999970LL, 846999974LL, 847999978LL, 848999974LL, 849999974LL, 850999972LL, 851999976LL, 852999966LL, 853999978LL, 854999972LL, 855999982LL, 856999980LL, 857999982LL, 858999974LL, 859999978LL, 860999976LL, 861999978LL, 862999974LL, 863999972LL, 864999972LL, 865999974LL, 866999968LL, 867999976LL, 868999970LL, 869999972LL, 870999968LL, 871999972LL, 872999980LL, 873999980LL, 874999976LL, 875999976LL, 876999974LL, 877999974LL, 878999974LL, 879999974LL, 880999974LL, 881999984LL, 882999980LL, 883999980LL, 884999982LL, 885999974LL, 886999970LL, 887999972LL, 888999976LL, 889999980LL, 890999974LL, 891999974LL, 892999976LL, 893999974LL, 894999972LL, 895999976LL, 896999974LL, 897999978LL, 898999972LL, 899999976LL, 900999974LL, 901999972LL, 902999968LL, 903999974LL, 904999974LL, 905999980LL, 906999972LL, 907999970LL, 908999972LL, 909999966LL, 910999976LL, 911999982LL, 912999974LL, 913999976LL, 914999974LL, 915999978LL, 916999974LL, 917999972LL, 918999970LL, 919999976LL, 920999974LL, 921999972LL, 922999972LL, 923999974LL, 924999978LL, 925999974LL, 926999974LL, 927999982LL, 928999968LL, 929999970LL, 930999962LL, 931999976LL, 932999970LL, 933999968LL, 934999962LL, 935999974LL, 936999968LL, 937999968LL, 938999976LL, 939999982LL, 940999980LL, 941999976LL, 942999978LL, 943999984LL, 944999976LL, 945999980LL, 946999978LL, 947999982LL, 948999978LL, 949999970LL, 950999970LL, 951999972LL, 952999978LL, 953999974LL, 954999976LL, 955999970LL, 956999978LL, 957999972LL, 958999974LL, 959999980LL, 960999974LL, 961999972LL, 962999972LL, 963999972LL, 964999974LL, 965999968LL, 966999968LL, 967999980LL, 968999978LL, 969999978LL, 970999978LL, 971999970LL, 972999966LL, 973999976LL, 974999974LL, 975999980LL, 976999970LL, 977999978LL, 978999972LL, 979999974LL, 980999968LL, 981999982LL, 982999970LL, 983999976LL, 984999972LL, 985999976LL, 986999972LL, 987999970LL, 988999970LL, 989999978LL, 990999972LL, 991999980LL, 992999966LL, 993999968LL, 994999966LL, 995999974LL, 996999974LL, 997999972LL, 998999970LL, 999999974LL, 1000999976LL, 1001999970LL, 1002999976LL, 1003999968LL, 1004999970LL, 1005999966LL, 1006999976LL, 1007999978LL, 1008999978LL, 1009999978LL, 1010999978LL, 1011999976LL, 1012999976LL, 1013999976LL, 1014999964LL, 1015999972LL, 1016999976LL, 1017999972LL, 1018999970LL, 1019999968LL, 1020999970LL, 1021999968LL, 1022999964LL, 1023999986LL, 1024999980LL, 1025999976LL, 1026999970LL, 1027999980LL, 1028999972LL, 1029999974LL, 1030999964LL, 1031999980LL, 1032999976LL, 1033999974LL, 1034999972LL, 1035999978LL, 1036999966LL, 1037999964LL, 1038999966LL, 1039999972LL, 1040999976LL, 1041999974LL, 1042999970LL, 1043999974LL, 1044999970LL, 1045999974LL, 1046999964LL, 1047999970LL, 1048999974LL, 1049999970LL, 1050999968LL, 1051999970LL, 1052999976LL, 1053999972LL, 1054999974LL, 1055999976LL, 1056999980LL, 1057999970LL, 1058999968LL, 1059999974LL, 1060999968LL, 1061999970LL, 1062999968LL, 1063999970LL, 1064999968LL, 1065999968LL, 1066999974LL, 1067999974LL, 1068999966LL, 1069999966LL, 1070999968LL, 1071999970LL, 1072999966LL, 1073999984LL, 1074999982LL, 1075999984LL, 1076999978LL, 1077999982LL, 1078999980LL, 1079999974LL, 1080999982LL, 1081999982LL, 1082999982LL, 1083999982LL, 1084999978LL, 1085999978LL, 1086999978LL, 1087999984LL, 1088999980LL, 1089999982LL, 1090999978LL, 1091999982LL, 1092999976LL, 1093999978LL, 1094999976LL, 1095999982LL, 1096999980LL, 1097999980LL, 1098999982LL, 1099999982LL, 1100999970LL, 1101999972LL, 1102999972LL, 1103999978LL, 1104999972LL, 1105999978LL, 1106999968LL, 1107999980LL, 1108999972LL, 1109999984LL, 1110999980LL, 1111999980LL, 1112999982LL, 1113999980LL, 1114999976LL, 1115999980LL, 1116999984LL, 1117999978LL, 1118999976LL, 1119999982LL, 1120999980LL, 1121999980LL, 1122999968LL, 1123999974LL, 1124999980LL, 1125999976LL, 1126999974LL, 1127999974LL, 1128999978LL, 1129999974LL, 1130999976LL, 1131999974LL, 1132999980LL, 1133999970LL, 1134999972LL, 1135999972LL, 1136999974LL, 1137999982LL, 1138999974LL, 1139999978LL, 1140999984LL, 1141999984LL, 1142999980LL, 1143999986LL, 1144999978LL, 1145999980LL, 1146999974LL, 1147999978LL, 1148999976LL, 1149999976LL, 1150999972LL, 1151999986LL, 1152999978LL, 1153999982LL, 1154999970LL, 1155999978LL, 1156999972LL, 1157999978LL, 1158999972LL, 1159999984LL, 1160999976LL, 1161999978LL, 1162999974LL, 1163999978LL, 1164999974LL, 1165999964LL, 1166999978LL, 1167999980LL, 1168999976LL, 1169999976LL, 1170999978LL, 1171999974LL, 1172999972LL, 1173999972LL, 1174999980LL, 1175999982LL, 1176999978LL, 1177999974LL, 1178999978LL, 1179999974LL, 1180999980LL, 1181999972LL, 1182999978LL, 1183999982LL, 1184999978LL, 1185999976LL, 1186999978LL, 1187999974LL, 1188999970LL, 1189999968LL, 1190999966LL, 1191999978LL, 1192999972LL, 1193999970LL, 1194999978LL, 1195999980LL, 1196999976LL, 1197999978LL, 1198999970LL, 1199999980LL, 1200999972LL, 1201999980LL, 1202999974LL, 1203999976LL, 1204999970LL, 1205999976LL, 1206999968LL, 1207999986LL, 1208999980LL, 1209999980LL, 1210999978LL, 1211999976LL, 1212999978LL, 1213999978LL, 1214999972LL, 1215999980LL, 1216999978LL, 1217999980LL, 1218999976LL, 1219999974LL, 1220999972LL, 1221999974LL, 1222999968LL, 1223999980LL, 1224999988LL, 1225999980LL, 1226999982LL, 1227999978LL, 1228999982LL, 1229999978LL, 1230999972LL, 1231999976LL, 1232999974LL, 1233999978LL, 1234999974LL, 1235999972LL, 1236999970LL, 1237999978LL, 1238999972LL, 1239999976LL, 1240999978LL, 1241999978LL, 1242999976LL, 1243999974LL, 1244999978LL, 1245999978LL, 1246999972LL, 1247999978LL, 1248999976LL, 1249999978LL, 1250999974LL, 1251999988LL, 1252999974LL, 1253999974LL, 1254999970LL, 1255999978LL, 1256999976LL, 1257999970LL, 1258999978LL, 1259999980LL, 1260999976LL, 1261999974LL, 1262999970LL, 1263999976LL, 1264999972LL, 1265999976LL, 1266999976LL, 1267999980LL, 1268999972LL, 1269999974LL, 1270999970LL, 1271999976LL, 1272999978LL, 1273999968LL, 1274999964LL, 1275999978LL, 1276999974LL, 1277999974LL, 1278999966LL, 1279999984LL, 1280999980LL, 1281999978LL, 1282999976LL, 1283999984LL, 1284999974LL, 1285999974LL, 1286999972LL, 1287999980LL, 1288999978LL, 1289999972LL, 1290999974LL, 1291999980LL, 1292999976LL, 1293999974LL, 1294999980LL, 1295999974LL, 1296999974LL, 1297999972LL, 1298999972LL, 1299999972LL, 1300999970LL, 1301999972LL, 1302999972LL, 1303999972LL, 1304999976LL, 1305999966LL, 1306999968LL, 1307999966LL, 1308999980LL, 1309999980LL, 1310999978LL, 1311999980LL, 1312999978LL, 1313999980LL, 1314999974LL, 1315999980LL, 1316999966LL, 1317999974LL, 1318999968LL, 1319999974LL, 1320999970LL, 1321999974LL, 1322999972LL, 1323999974LL, 1324999968LL, 1325999976LL, 1326999974LL, 1327999974LL, 1328999968LL, 1329999978LL, 1330999970LL, 1331999974LL, 1332999964LL, 1333999974LL, 1334999968LL, 1335999972LL, 1336999980LL, 1337999980LL, 1338999970LL, 1339999968LL, 1340999972LL, 1341999966LL, 1342999980LL, 1343999982LL, 1344999982LL, 1345999980LL, 1346999978LL, 1347999980LL, 1348999980LL, 1349999972LL, 1350999974LL, 1351999980LL, 1352999982LL, 1353999978LL, 1354999978LL, 1355999976LL, 1356999978LL, 1357999972LL, 1358999982LL, 1359999976LL, 1360999974LL, 1361999976LL, 1362999970LL, 1363999974LL, 1364999972LL, 1365999978LL, 1366999972LL, 1367999984LL, 1368999980LL, 1369999980LL, 1370999970LL, 1371999976LL, 1372999976LL, 1373999974LL, 1374999970LL, 1375999988LL, 1376999978LL, 1377999980LL, 1378999972LL, 1379999986LL, 1380999980LL, 1381999972LL, 1382999968LL, 1383999976LL, 1384999976LL, 1385999974LL, 1386999972LL, 1387999974LL, 1388999974LL, 1389999970LL, 1390999970LL, 1391999976LL, 1392999972LL, 1393999980LL, 1394999980LL, 1395999978LL, 1396999978LL, 1397999974LL, 1398999974LL, 1399999976LL, 1400999982LL, 1401999978LL, 1402999980LL, 1403999970LL, 1404999970LL, 1405999968LL, 1406999968LL, 1407999978LL, 1408999970LL, 1409999980LL, 1410999978LL, 1411999980LL, 1412999976LL, 1413999972LL, 1414999970LL, 1415999978LL, 1416999974LL, 1417999976LL, 1418999978LL, 1419999974LL, 1420999972LL, 1421999970LL, 1422999978LL, 1423999984LL, 1424999970LL, 1425999974LL, 1426999976LL, 1427999976LL, 1428999972LL, 1429999978LL, 1430999972LL, 1431999976LL, 1432999974LL, 1433999974LL, 1434999976LL, 1435999970LL, 1436999974LL, 1437999974LL, 1438999972LL, 1439999978LL, 1440999970LL, 1441999972LL, 1442999976LL, 1443999980LL, 1444999976LL, 1445999978LL, 1446999964LL, 1447999974LL, 1448999968LL, 1449999970LL, 1450999976LL, 1451999976LL, 1452999976LL, 1453999974LL, 1454999972LL, 1455999978LL, 1456999976LL, 1457999974LL, 1458999970LL, 1459999976LL, 1460999974LL, 1461999976LL, 1462999968LL, 1463999974LL, 1464999980LL, 1465999976LL, 1466999974LL, 1467999964LL, 1468999972LL, 1469999968LL, 1470999966LL, 1471999972LL, 1472999974LL, 1473999968LL, 1474999966LL, 1475999966LL, 1476999978LL, 1477999976LL, 1478999968LL, 1479999982LL, 1480999982LL, 1481999978LL, 1482999978LL, 1483999980LL, 1484999978LL, 1485999976LL, 1486999976LL, 1487999982LL, 1488999980LL, 1489999974LL, 1490999968LL, 1491999974LL, 1492999966LL, 1493999980LL, 1494999970LL, 1495999978LL, 1496999976LL, 1497999976LL, 1498999972LL, 1499999976LL, 1500999970LL, 1501999974LL, 1502999968LL, 1503999978LL, 1504999972LL, 1505999972LL, 1506999966LL, 1507999980LL, 1508999974LL, 1509999982LL, 1510999980LL, 1511999976LL, 1512999976LL, 1513999970LL, 1514999978LL, 1515999976LL, 1516999972LL, 1517999968LL, 1518999976LL, 1519999976LL, 1520999974LL, 1521999972LL, 1522999974LL, 1523999974LL, 1524999970LL, 1525999970LL, 1526999976LL, 1527999974LL, 1528999978LL, 1529999972LL, 1530999976LL, 1531999974LL, 1532999966LL, 1533999964LL, 1534999964LL, 1535999980LL, 1536999974LL, 1537999978LL, 1538999968LL, 1539999976LL, 1540999968LL, 1541999972LL, 1542999966LL, 1543999980LL, 1544999976LL, 1545999978LL, 1546999974LL, 1547999978LL, 1548999970LL, 1549999972LL, 1550999974LL, 1551999982LL, 1552999976LL, 1553999982LL, 1554999968LL, 1555999970LL, 1556999966LL, 1557999972LL, 1558999968LL, 1559999968LL, 1560999974LL, 1561999974LL, 1562999970LL, 1563999970LL, 1564999982LL, 1565999972LL, 1566999972LL, 1567999974LL, 1568999978LL, 1569999976LL, 1570999970LL, 1571999974LL, 1572999976LL, 1573999972LL, 1574999970LL, 1575999966LL, 1576999966LL, 1577999972LL, 1578999974LL, 1579999974LL, 1580999974LL, 1581999970LL, 1582999970LL, 1583999972LL, 1584999970LL, 1585999978LL, 1586999968LL, 1587999970LL, 1588999968LL, 1589999970LL, 1590999966LL, 1591999966LL, 1592999974LL, 1593999980LL, 1594999974LL, 1595999978LL, 1596999976LL, 1597999966LL, 1598999966LL, 1599999976LL, 1600999970LL, 1601999970LL, 1602999966LL, 1603999972LL, 1604999968LL, 1605999966LL, 1606999964LL, 1607999976LL, 1608999968LL, 1609999966LL, 1610999980LL, 1611999982LL, 1612999980LL, 1613999974LL, 1614999978LL, 1615999984LL, 1616999978LL, 1617999980LL, 1618999966LL, 1619999976LL, 1620999970LL, 1621999978LL, 1622999976LL, 1623999982LL, 1624999978LL, 1625999976LL, 1626999976LL, 1627999980LL, 1628999982LL, 1629999974LL, 1630999974LL, 1631999982LL, 1632999976LL, 1633999976LL, 1634999974LL, 1635999982LL, 1636999978LL, 1637999976LL, 1638999974LL, 1639999982LL, 1640999972LL, 1641999968LL, 1642999974LL, 1643999970LL, 1644999978LL, 1645999970LL, 1646999974LL, 1647999976LL, 1648999974LL, 1649999984LL, 1650999980LL, 1651999976LL, 1652999976LL, 1653999980LL, 1654999974LL, 1655999978LL, 1656999978LL, 1657999978LL, 1658999976LL, 1659999974LL, 1660999980LL, 1661999980LL, 1662999968LL, 1663999980LL, 1664999972LL, 1665999978LL, 1666999972LL, 1667999974LL, 1668999968LL, 1669999976LL, 1670999968LL, 1671999978LL, 1672999968LL, 1673999972LL, 1674999970LL, 1675999970LL, 1676999966LL, 1677999978LL, 1678999980LL, 1679999984LL, 1680999982LL, 1681999984LL, 1682999980LL, 1683999972LL, 1684999972LL, 1685999974LL, 1686999974LL, 1687999976LL, 1688999980LL, 1689999972LL, 1690999974LL, 1691999970LL, 1692999978LL, 1693999974LL, 1694999974LL, 1695999978LL, 1696999978LL, 1697999974LL, 1698999974LL, 1699999974LL, 1700999974LL, 1701999972LL, 1702999972LL, 1703999976LL, 1704999978LL, 1705999966LL, 1706999972LL, 1707999978LL, 1708999972LL, 1709999972LL, 1710999966LL, 1711999982LL, 1712999976LL, 1713999980LL, 1714999974LL, 1715999982LL, 1716999970LL, 1717999974LL, 1718999966LL, 1719999978LL, 1720999980LL, 1721999976LL, 1722999972LL, 1723999978LL, 1724999974LL, 1725999974LL, 1726999962LL, 1727999972LL, 1728999974LL, 1729999972LL, 1730999968LL, 1731999974LL, 1732999968LL, 1733999968LL, 1734999962LL, 1735999976LL, 1736999980LL, 1737999970LL, 1738999974LL, 1739999972LL, 1740999972LL, 1741999968LL, 1742999974LL, 1743999972LL, 1744999982LL, 1745999980LL, 1746999980LL, 1747999980LL, 1748999968LL, 1749999976LL, 1750999974LL, 1751999976LL, 1752999976LL, 1753999974LL, 1754999974LL, 1755999974LL, 1756999974LL, 1757999974LL, 1758999974LL, 1759999974LL, 1760999970LL, 1761999974LL, 1762999972LL, 1763999984LL, 1764999974LL, 1765999980LL, 1766999974LL, 1767999980LL, 1768999976LL, 1769999982LL, 1770999974LL, 1771999974LL, 1772999970LL, 1773999970LL, 1774999972LL, 1775999972LL, 1776999968LL, 1777999976LL, 1778999978LL, 1779999980LL, 1780999970LL, 1781999974LL, 1782999972LL, 1783999974LL, 1784999976LL, 1785999976LL, 1786999974LL, 1787999974LL, 1788999972LL, 1789999972LL, 1790999972LL, 1791999976LL, 1792999974LL, 1793999974LL, 1794999968LL, 1795999978LL, 1796999976LL, 1797999972LL, 1798999968LL, 1799999976LL, 1800999976LL, 1801999974LL, 1802999968LL, 1803999972LL, 1804999972LL, 1805999968LL, 1806999972LL, 1807999974LL, 1808999972LL, 1809999974LL, 1810999968LL, 1811999980LL, 1812999978LL, 1813999972LL, 1814999970LL, 1815999970LL, 1816999976LL, 1817999972LL, 1818999968LL, 1819999966LL, 1820999980LL, 1821999976LL, 1822999974LL, 1823999982LL, 1824999974LL, 1825999974LL, 1826999968LL, 1827999976LL, 1828999978LL, 1829999974LL, 1830999970LL, 1831999978LL, 1832999976LL, 1833999974LL, 1834999968LL, 1835999972LL, 1836999968LL, 1837999970LL, 1838999968LL, 1839999976LL, 1840999966LL, 1841999974LL, 1842999966LL, 1843999972LL, 1844999966LL, 1845999972LL, 1846999966LL, 1847999974LL, 1848999978LL, 1849999978LL, 1850999978LL, 1851999974LL, 1852999974LL, 1853999974LL, 1854999974LL, 1855999982LL, 1856999970LL, 1857999968LL, 1858999970LL, 1859999970LL, 1860999968LL, 1861999962LL, 1862999968LL, 1863999976LL, 1864999974LL, 1865999970LL, 1866999976LL, 1867999968LL, 1868999968LL, 1869999962LL, 1870999972LL, 1871999974LL, 1872999968LL, 1873999968LL, 1874999970LL, 1875999968LL, 1876999966LL, 1877999976LL, 1878999962LL, 1879999982LL, 1880999978LL, 1881999980LL, 1882999976LL, 1883999976LL, 1884999976LL, 1885999978LL, 1886999972LL, 1887999984LL, 1888999972LL, 1889999976LL, 1890999970LL, 1891999980LL, 1892999974LL, 1893999978LL, 1894999968LL, 1895999982LL, 1896999976LL, 1897999978LL, 1898999978LL, 1899999970LL, 1900999970LL, 1901999970LL, 1902999968LL, 1903999972LL, 1904999968LL, 1905999978LL, 1906999976LL, 1907999974LL, 1908999976LL, 1909999976LL, 1910999968LL, 1911999970LL, 1912999984LL, 1913999978LL, 1914999978LL, 1915999972LL, 1916999978LL, 1917999974LL, 1918999972LL, 1919999980LL, 1920999984LL, 1921999974LL, 1922999970LL, 1923999972LL, 1924999970LL, 1925999972LL, 1926999964LL, 1927999972LL, 1928999972LL, 1929999974LL, 1930999974LL, 1931999968LL, 1932999968LL, 1933999968LL, 1934999972LL, 1935999980LL, 1936999974LL, 1937999978LL, 1938999972LL, 1939999978LL, 1940999970LL, 1941999978LL, 1942999964LL, 1943999970LL, 1944999970LL, 1945999966LL, 1946999974LL, 1947999976LL, 1948999976LL, 1949999974LL, 1950999972LL, 1951999980LL, 1952999976LL, 1953999970LL, 1954999970LL, 1955999978LL, 1956999972LL, 1957999972LL, 1958999966LL, 1959999974LL, 1960999972LL, 1961999968LL, 1962999984LL, 1963999982LL, 1964999972LL, 1965999970LL, 1966999972LL, 1967999976LL, 1968999972LL, 1969999972LL, 1970999970LL, 1971999976LL, 1972999970LL, 1973999972LL, 1974999970LL, 1975999970LL, 1976999974LL, 1977999970LL, 1978999970LL, 1979999978LL, 1980999974LL, 1981999972LL, 1982999972LL, 1983999980LL, 1984999976LL, 1985999966LL, 1986999966LL, 1987999968LL, 1988999968LL, 1989999966LL, 1990999966LL, 1991999974LL, 1992999974LL, 1993999974LL, 1994999972LL, 1995999972LL, 1996999970LL, 1997999970LL, 1998999972LL, 1999999974LL, 2000999972LL, 2001999976LL, 2002999968LL, 2003999970LL, 2004999968LL, 2005999976LL, 2006999972LL, 2007999968LL, 2008999966LL, 2009999970LL, 2010999964LL, 2011999966LL, 2012999962LL, 2013999976LL, 2014999972LL, 2015999978LL, 2016999972LL, 2017999978LL, 2018999966LL, 2019999978LL, 2020999976LL, 2021999978LL, 2022999974LL, 2023999976LL, 2024999976LL, 2025999976LL, 2026999976LL, 2027999976LL, 2028999976LL, 2029999964LL, 2030999972LL, 2031999972LL, 2032999972LL, 2033999976LL, 2034999972LL, 2035999972LL, 2036999972LL, 2037999970LL, 2038999972LL, 2039999968LL, 2040999974LL, 2041999970LL, 2042999970LL, 2043999968LL, 2044999972LL, 2045999964LL, 2046999972LL, 2047999986LL, 2048999980LL, 2049999980LL, 2050999966LL, 2051999976LL, 2052999970LL, 2053999970LL, 2054999964LL, 2055999980LL, 2056999972LL, 2057999972LL, 2058999968LL, 2059999974LL, 2060999970LL, 2061999964LL, 2062999966LL, 2063999980LL, 2064999972LL, 2065999976LL, 2066999966LL, 2067999974LL, 2068999968LL, 2069999972LL, 2070999966LL, 2071999978LL, 2072999968LL, 2073999966LL, 2074999962LL, 2075999964LL, 2076999974LL, 2077999966LL, 2078999968LL, 2079999972LL, 2080999978LL, 2081999976LL, 2082999976LL, 2083999974LL, 2084999974LL, 2085999970LL, 2086999970LL, 2087999974LL, 2088999974LL, 2089999970LL, 2090999978LL, 2091999974LL, 2092999976LL, 2093999964LL, 2094999966LL, 2095999970LL, 2096999964LL, 2097999974LL, 2098999972LL, 2099999970LL, 2100999966LL, 2101999968LL, 2102999966LL, 2103999970LL, 2104999970LL, 2105999976LL, 2106999972LL, 2107999972LL, 2108999970LL, 2109999974LL, 2110999966LL, 2111999976LL, 2112999968LL, 2113999980LL, 2114999974LL, 2115999970LL, 2116999966LL, 2117999968LL, 2118999964LL, 2119999974LL, 2120999968LL, 2121999968LL, 2122999972LL, 2123999970LL, 2124999968LL, 2125999968LL, 2126999966LL, 2127999970LL, 2128999964LL, 2129999968LL, 2130999970LL, 2131999968LL, 2132999964LL, 2133999974LL, 2134999972LL, 2135999974LL, 2136999978LL, 2137999966LL, 2138999964LL, 2139999966LL, 2140999970LL, 2141999968LL, 2142999962LL, 2143999970LL, 2144999968LL, 2145999966LL, 2146999962LL};

int dist(ll i, ll j){
   int k = 0;
   if(i == j) 
     return 0;

   if (i % 2 == 1){
     ++k;                  
     i += 2*(i%4 == 1) - 1;
   }
   if(j % 2 == 1){
     ++k;
     j += 2*(j%4 == 1) - 1;
   }                  
   return k + dist(i/2,j/2);
}

ll pref(ll l){
  int j =(l-1)/BL;
  ll sum = ans[j];
  ll start = (BL*j)+1;
  for(ll i = start; i < l; ++i) 
     sum += dist(i,i+1) - 1;
  return sum;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  /*ll res = 0;

  cout << "ll ans[] = {0LL,";

  for (ll i = 1; i < (1LL<<31); i++){
     res += dist(i,i+1) - 1;
     if (i % BL == 0)
        cout << res <<"LL, ",cerr<<i<<endl;
  }
  return 0; */
                  
  ll a,b;
  while (cin>>a>>b){
     if (a > b) swap(a,b);
     cout<< pref(b) - pref(a) << endl;
  }
  return 0;
};