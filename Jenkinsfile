pipeline {
    agent any

    environment {
        PATH = "$WORKSPACE/cmake-3.26.4-linux-x86_64/bin:$PATH"
    }

    stages {
        stage('Install CMake') {
            steps {
                sh '''
                # Download and extract CMake
                echo "Installing CMake..."
                curl -LO https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-linux-x86_64.tar.gz
                tar -xvf cmake-3.26.4-linux-x86_64.tar.gz
                echo "CMake installed successfully."
                '''
            }
        }

        stage('Debug PATH and Environment') {
            steps {
                sh '''
                echo "Current PATH: $PATH"
                which cmake
                cmake --version
                '''
            }
        }

        stage('Checkout Code') {
            steps {
                git 'https://github.com/gopuman/Jenkins-cmake-test'
            }
        }

        stage('Configure and Build') {
            steps {
                sh '''
                echo "Configuring and Building..."
                mkdir -p build
                cd build
                cmake ..
                make
                '''
            }
        }

        stage('Run Tests') {
            steps {
                sh '''
                echo "Running Tests..."
                cd build
                ctest --verbose
                '''
            }
        }

        stage('Archive Artifacts') {
            steps {
                archiveArtifacts artifacts: 'build/**', fingerprint: true
            }
        }
    }

    post {
        always {
            echo 'Pipeline completed.'
        }
        success {
            echo 'Pipeline succeeded!'
        }
        failure {
            echo 'Pipeline failed!'
        }
    }
}
