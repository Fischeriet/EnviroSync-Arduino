#include "HTMLPages.h"

const char* MAIN_PAGE = R"(
<!DOCTYPE html>
<html>
<head>
    <title>WiFi Opsætning</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { font-family: Arial; margin: 0 auto; padding: 20px; max-width: 400px; }
        .form-group { margin-bottom: 15px; }
        label { display: block; margin-bottom: 5px; }
        input[type="text"], input[type="password"] {
            width: 100%;
            padding: 8px;
            border: 1px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
        }
        button {
            background-color: #4CAF50;
            color: white;
            padding: 10px 15px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            width: 100%;
        }
        button:hover { background-color: #45a049; }
    </style>
</head>
<body>
    <h2>WiFi Opsætning</h2>
    <form action="" method="POST" id="test">
        <div class="form-group">
            <label for="ssid">WiFi Navn (SSID):</label>
            <input type="text" id="ssid" name="ssid" required>
        </div>
        <div class="form-group">
            <label for="password">Password:</label>
            <input type="password" id="password" name="password" required>
        </div>
        <button type="submit">Tilslut</button>
    </form>
    <script>
        document.getElementById("test").addEventListener("submit", async (e) => {
            e.preventDefault();
            const ssid = document.getElementById("ssid").value;
            const password = document.getElementById("password").value;

            try {
                fetch('/update', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({
                        ssid: ssid,
                        password: password
                    })
                });

                location.href = "/loading";
            } catch (error) {
                alert("Der skete en fejl: " + error);
            }
        });

        </script>
</body>
</html>
)";

const char* LOADING_PAGE = R"(
<!DOCTYPE html>
<html>
<head>
    <title>Forbinder...</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { font-family: Arial; text-align: center; padding-top: 50px; }
        .loader {
            border: 8px solid #f3f3f3;
            border-top: 8px solid #3498db;
            border-radius: 50%;
            width: 50px;
            height: 50px;
            animation: spin 1s linear infinite;
            margin: 20px auto;
        }
        @keyframes spin {
            0% { transform: rotate(0deg); }
            100% { transform: rotate(360deg); }
        }
    </style>
</head>
<body>
    <h2>Forbinder til WiFi...</h2>
    <div class="loader"></div>
    <p>Vent venligst mens enheden forbinder til det valgte netværk.</p>
</body>
</html>
)";