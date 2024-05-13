fun readTree(n: Int) : List<BooleanArray> {
    val p = listOf(null) + readInts().map { it - 1 }
    return List(n) { a -> BooleanArray(n) { b -> a in generateSequence(b) { p[it] } } }
}
fun main() {
    val n = readInt()
    val t1 = readTree(n)
    val t2 = readTree(n)
    val masks = LongArray(n) { a ->
        (0 until n).filter { b -> a != b && t1[a][b] == t2[a][b] && t1[b][a] == t2[b][a] }.sumOf { 1L shl it }
    }
    val data = mutableMapOf<Long, Int>()
    data[0] = 0
    fun compute(mask: Long) : Int = data.getOrPut(mask) {
        val index = mask.countTrailingZeroBits()
        maxOf(compute(mask xor (1L shl index)), compute(mask and masks[index]) + 1)
    }
    println(2 * (n - compute((1L shl n) - 1)))
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }