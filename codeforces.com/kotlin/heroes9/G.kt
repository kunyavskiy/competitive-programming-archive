fun main() {
    repeat(readInt()) test@{
        readInt()
        val a = readLongs()
        val x = a.first()
        val y = a.firstOrNull { it % x != 0L }
        val b = buildList {
            for (i in 1..a.size) { add(x * i) }
            if (y != null) {
                for (i in 1..a.size) { add(y * i) }
            }
            sort()
        }.distinct().take(a.size)
        println(if (a == b) "VALID" else "INVALID")
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }