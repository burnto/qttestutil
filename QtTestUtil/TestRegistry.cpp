/*
 * Copyright (C) 2008  Remko Troncon
 * Licensed under the MIT license.
 * See COPYING for license details.
 */

#include "QtTestUtil/TestRegistry.h"

#include <QtTest/QtTest>

namespace QtTestUtil {

TestRegistry* TestRegistry::getInstance() {
	static TestRegistry registry;
	return &registry;
}

void TestRegistry::registerTest(QObject* test) {
    tests_ << test;
}

int TestRegistry::runTests(int argc, char* argv[]) {
    QStringList args = QCoreApplication::arguments();
    runTests(args);
}

int TestRegistry::runTests(QStringList args) {
    int result = 0;
    int xunitoutFlagIndex = args.indexOf("-xunitout");

    foreach(QObject *test, tests_) {
        QStringList testArgs = args;
        if(xunitoutFlagIndex >= 0 && args.length() > xunitoutFlagIndex + 1) {
            QDir outDir(args.at(xunitoutFlagIndex + 1));
            testArgs << "-o";
            testArgs << outDir.filePath(test->metaObject()->className());
        }
        result |= QTest::qExec(test, testArgs);
    }
    return result;
}
}
