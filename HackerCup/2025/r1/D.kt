private fun solve(): Boolean {
    readln()
    val s = readln()

    var a = 0
    for (i in s) {
        if (i == 'A') {
            a++
        } else {
            a--
        }
        a = maxOf(a, 0)
    }
    return a > 0
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        println(if (solve()) "Alice" else "Bob")
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }