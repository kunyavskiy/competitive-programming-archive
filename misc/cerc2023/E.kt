fun main() {
    val a = getSchedule()
    val b = getSchedule()
    val all = (a.keys + b.keys).toList().sorted()
    val ans = all.map { it to b.getOrDefault(it, 0) - a.getOrDefault(it, 0) }
        .filter { it.second != 0 }
    if (ans.isEmpty()) {
        println("No differences found.")
    } else {
        for ((k, v) in ans) {
            println("%s %+d".format(k, v))
        }
    }
}

private fun getSchedule() =
    buildList {
        while (true) {
            val s = readln()
            if (s[0] == '-' || s[0] == '=') break
            val (a, b, name) = s.split(" ")
            add(name to (b.toInt() - a.toInt()))
        }
    }.groupBy { it.first }.mapValues { (_, v) -> v.sumOf { it.second } }

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }