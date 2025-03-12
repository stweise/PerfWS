package main

import (
	"fmt"
	"log"
	"math/rand"
	"net/http"
	"os"
	"sync"
)

var requestHistory []string
var historyMutex sync.Mutex

func fib(n int) int {
	if n <= 1 {
		return n
	}
	return fib(n-1) + fib(n-2)
}

// Simulated "Database Query" (Reads a file on every request)
func slowDatabaseRead() string {
	data, err := os.ReadFile("data.txt") // Reads file every time
	if err != nil {
		return "ERROR: Failed to read file"
	}
	return string(data)
}

func handler(w http.ResponseWriter, r *http.Request) {
	n := rand.Intn(30) + 10

	var result int
	var wg sync.WaitGroup
	wg.Add(1)
	go func() {
		defer wg.Done()
		result = fib(n)
	}()
	wg.Wait()

	dbResult := slowDatabaseRead()

	historyMutex.Lock()
	requestHistory = append(requestHistory, fmt.Sprintf("Computed fib(%d) = %d", n, result))
	historyMutex.Unlock()

	fmt.Fprintf(w, "Fibonacci(%d) = %d\nDB Response: %s\n", n, result, dbResult)
}

func main() {
	err := os.WriteFile("data.txt", []byte("This is test data!"), 0644)
	if err != nil {
		log.Fatal(err)
	}

	http.HandleFunc("/", handler)
	log.Println("Starting inefficient server on :8080")
	log.Fatal(http.ListenAndServe(":8080", nil))
}
