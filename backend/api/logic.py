
from datetime import date


class ZodiacSign:
    """
    The every attributes structure is ((start date), (end date), (Russian name)).
    The every tuple of date struct is (day, month).
    """

    _aries =         ((21, 3), (20, 4), ('Овен'))
    _taurus =        ((21, 4), (21, 5), ('Телец'))
    _gemini =        ((22, 5), (21, 6), ('Близнецы'))
    _cancer =        ((22, 6), (22, 7), ('Рак'))
    _leo =           ((23, 7), (21, 8), ('Лев'))
    _virgo =         ((22, 8), (23, 9), ('Дева'))
    _libra =         ((24, 9), (23, 10), ('Весы'))
    _scorpio =       ((22, 10), (24, 11), ('Скорпион'))
    _sagittarius =   ((23, 11), (22, 12), ('Стрелец'))
    _capricorn =     ((23, 12), (20, 1), ('Козерог'))
    _aquarius =      ((21, 1), (19, 2), ('Водолей'))
    _pisces =        ((20, 2), (20, 3), ('Рыбы'))

    validated_data = { }

    @classmethod
    def get_attributes(cls):
        return (
            cls._aries,
            cls._taurus,
            cls._gemini,
            cls._cancer,
            cls._leo,
            cls._virgo,
            cls._libra,
            cls._scorpio,
            cls._sagittarius,
            cls._capricorn,
            cls._aquarius,
            cls._pisces
        )

    def get_sign(self, birthday):
        year = birthday.year
        for sign in self.get_attributes():
            start, stop, name = sign
            if date(year, start[1], start[0]) <= birthday <= date(year, stop[1], stop[0]):
                return name
        return self._capricorn[2]

    def _set_zodiac_sign(self):
        zodiac = self.get_sign(self.validated_data['birthday'])
        self.validated_data['zodiac'] = zodiac
