#include "scores.h"
#include "ui_scores.h"
#include <QTimer>

/* initializing the constructor */
scores::scores(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::scores)
{
    ui->setupUi(this);
    getaddress();

    /* calls get address every 10 seconds so that high score is refreshed every 10 seconds */
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getaddress()));
    timer->start(10000);

}

scores::~scores()
{
    delete ui;
}

/* CURL Write function */
std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out){
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}


void scores::getaddress()
{
    string link;
    const std::string url("https://matiusulung.com/se.json");

    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &link);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    json obj = json::parse(link);
    link = obj["link"];
    //appending to get scores
    link.append("/getscores");

    getscores(link);
}

void scores::getscores(string link)
{
    /* CURL performs get request to obtain high scores */
    string scores;
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &scores);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    /* calling function present scores to display high scores after getting high scores
     * from the server
     */
    presentscores(scores);
}

void scores::presentscores(string scores)
{
    json object = json::parse(scores.c_str());
    vector< pair <int,string> > vect;
    for (auto& element : object) {
        for (int i = 0; i < 10; i++){
            string a = element[i]["game-username"];
            int b = element[i]["score"];
            vect.push_back(make_pair(b,a));
        }
    }
    sort(vect.begin(), vect.end());
    QString username[10];
    QString score[10];
    for (int i = 9; i >= 0; i--) {
        QString an = vect[i].second.c_str();
        QString bn = QString::number(vect[i].first);
        username[i] = QString("%1").arg(an);
        score[i] = QString("%1").arg(bn);
    }
    ui->user0->setText(username[9]);
    ui->score0->setText(score[9]);
    ui->user1->setText(username[8]);
    ui->score1->setText(score[8]);
    ui->user2->setText(username[7]);
    ui->score2->setText(score[7]);
    ui->user3->setText(username[6]);
    ui->score3->setText(score[6]);
    ui->user4->setText(username[5]);
    ui->score4->setText(score[5]);
    ui->user5->setText(username[4]);
    ui->score5->setText(score[4]);
    ui->user6->setText(username[3]);
    ui->score6->setText(score[3]);
    ui->user7->setText(username[2]);
    ui->score7->setText(score[2]);
    ui->user8->setText(username[1]);
    ui->score8->setText(score[1]);
    ui->user9->setText(username[0]);
    ui->score9->setText(score[0]);

}


void scores::on_goback_clicked()
{
    /* emits the signal when back button is clicked, which takes back to home screen */
    emit backClicked();
}
