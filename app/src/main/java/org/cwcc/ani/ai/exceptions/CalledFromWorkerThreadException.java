package org.cwcc.ani.ai.exceptions;

public class CalledFromWorkerThreadException extends RuntimeException {

    public CalledFromWorkerThreadException(String message) {
        super(message);
    }
}
