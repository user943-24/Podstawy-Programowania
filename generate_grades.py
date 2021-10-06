import os
import sys
import hashlib
import json
import datetime


def main(args):
    grades_file = args[0]
    print('grades from: {}'.format(grades_file))

    grades_source = {}
    with open(grades_file, 'r') as ifstream:
        grades_source = json.loads(ifstream.read())

    meetings = grades_source['meetings']
    students = grades_source['students']
    print('students: {}'.format(len(students.keys())))
    print('meetings: {}'.format(', '.join(map(lambda _: _['date'], meetings))))

    PASSING_GRADE = 3.0

    failing_students = []
    for index, data in students.items():
        name = data['name']
        nick = (data['nick'] or None)

        gs = []
        for i, m in enumerate(meetings):
            if datetime.datetime.strptime(m['date'], '%Y-%m-%d') > datetime.datetime.now():
                continue

            grade = 2.0
            try:
                grade = data['grades'][i]
            except IndexError:
                pass

            if m.get('empty', False):
                grade = 0.0

            gs.append((m, grade,))

        gs_useful = list(filter(lambda _: _[1], gs))
        average_grade = sum(map(lambda _: _[1], gs_useful)) / len(gs_useful)
        if average_grade < PASSING_GRADE:
            failing_students.append((index, name, nick, average_grade,))

        print('  s{}: {} ({}): {:4.2f}'.format(
            index,
            name,
            (nick or 'does not have a nick!'),
            average_grade,
        ))

        if nick is None:
            continue

        student_id = '{}+s{}'.format(nick, index)
        student_id = hashlib.sha1(student_id.encode('utf-8')).hexdigest()
        with open(os.path.join('grades', student_id), 'w') as ofstream:
            ofstream.write('nick:  {}\n'.format(nick))
            ofstream.write('ocena: {:4.2f}\n'.format(average_grade))
            ofstream.write('\n')

            ofstream.write('+------------+------\n')
            ofstream.write('|       Data | Ocena\n')
            ofstream.write('+------------+------\n')
            for date, grade in gs:
                ofstream.write('| {} | {:4.2f}  ({})\n'.format(
                    date['date'],
                    grade,
                    date['comment'],
                ))
            ofstream.write('+------------+------\n')

    print('failing: {} of {} ({:5.2f}%)'.format(
        len(failing_students),
        len(students.keys()),
        ((len(failing_students) / len(students.keys())) * 100.0),
    ))
    for index, name, nick, average_grade in failing_students:
        print('  s{}: {} ({}): {:4.2f}'.format(index, name, nick,
            average_grade))

    return 0


exit(main(sys.argv[1:]))
