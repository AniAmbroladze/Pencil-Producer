#ifndef scores_H
#define scores_H

#include <QMainWindow>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

using namespace nlohmann;


namespace Ui {
class scores;
}
/**
 * @brief   A singleton class which represents scores screen GUI class.
 */
class scores : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief constructor of the scores class
     */
    explicit scores(QWidget *parent = nullptr);
    /**
     * @brief function to get scores from the server
     * @param link is the website link from where we get scores
     */
    void getscores(string link);

    /**
     * @brief function to display the scores in the UI after we get
     * scores from the server
     * @param scores is the json string that we get from the server
     */
    void presentscores(string scores);

    /**
     * destructor of the scoreboad class
     */
    ~scores();

private slots:
    /**
     * @brief function that will take action when back button
     * is clicked on the UI
     */
    void on_goback_clicked();

    /**
     * @brief function to get link of the server
     */
    void getaddress();

private:
    /**
     * @brief pointer to the UI
     */
    Ui::scores *ui;

signals:
    /**
     * @brief emits this signal when back button is clicked in the UI
     * to get back to homescreen
     */
    void backClicked();
};

#endif // scores_H
