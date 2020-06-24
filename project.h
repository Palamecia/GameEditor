#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>

class Project {
    Q_DISABLE_COPY(Project)
public:
    static Project &instance();

    QString getPath() const;

private:
    Project();
};

#endif // PROJECT_H
