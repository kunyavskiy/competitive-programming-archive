fun main() {
    repeat(readInt()) {
        readInt()
        val d = mutableListOf(mutableListOf<Long>())
        for (i in readLongs()) {
            if (i == 0L) {
                d.add(mutableListOf())
            } else {
                d.last().add(i)
            }
        }
        println(d.sumOf { l -> 2 * l.sum() - ((l.indices step 2).takeIf { l.size % 2 == 1 }?.maxOfOrNull { l[it] } ?: 0) })
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }